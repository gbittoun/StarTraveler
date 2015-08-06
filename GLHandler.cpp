#include "GLHandler.h"
#include "ShaderLoader.h"

#include <vector>


GLHandler::GLHandler() :
	ErrorStateBase()
{
}

GLHandler::~GLHandler()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteProgram(program);
}

/* general OpenGL initialization function */
ErrorStateBase::ErrorCode GLHandler::initGL()
{
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Glew initialization failed" << std::endl;
        errorState = GLEW_INIT_FAILED;
    }

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    if (checkState())
        prepareProgram();

    if (checkState())
        prepareObjects();

    return errorState;
}

void GLHandler::prepareProgram()
{
    ShaderLoader loader;
    loader.setShaderFile(GL_VERTEX_SHADER, "VertexStarShader.sl");
    loader.setShaderFile(GL_FRAGMENT_SHADER, "FragmentStarShader.sl");

    errorState = loader.generateProgram(program);
}

void GLHandler::setUniform(std::string const & uniformName, std::vector<GLfloat> const & values)
{
    uniformMap[uniformName] = values;
}

void GLHandler::setStarField(std::vector<Star> const & starField)
{
    this->starField = starField;
}

void GLHandler::prepareObjects()
{
    glUseProgram(program);

    // Set transformation matrix
    for (int i = 0 ; i < 4 ; ++i)
        for (int j = 0 ; j < 4 ; ++j)
            if (i == j)
                uniformMap["transformation_matrix"].push_back(1);
            else
                uniformMap["transformation_matrix"].push_back(0);

    for (auto uniform : uniformMap)
    {
        GLint location = glGetUniformLocation(program, (GLchar*)uniform.first.c_str());
        if (location < 0)
        {
            std::cout << "Couldn’t retrieve location for uniform " << uniform.first << std::endl;
            continue;
        }

        glUniformMatrix4fv(location, 1, GL_FALSE, &uniform.second[0]);
        if (GL_INVALID_OPERATION == glGetError())
        {
            std::cout << "An error occured while setting values for uniform " << uniform.first << std::endl;
        }
    }

    GLint nbAttributes;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &nbAttributes);

    GLint starLocation = glGetAttribLocation(program, "star");
    GLint magnitudeLocation = glGetAttribLocation(program, "magnitude");
    GLint colorLocation = glGetAttribLocation(program, "input_color");

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Star)*starField.size(), &starField[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(starLocation);
    glVertexAttribPointer(starLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)offsetof(Star, position));

    glEnableVertexAttribArray(magnitudeLocation);
    glVertexAttribPointer(magnitudeLocation, 1, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)offsetof(Star, magnitude));

    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Star), (void*)offsetof(Star, color));

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLHandler::resizeWindow(int width, int height)
{
    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
}

void GLHandler::drawGLScene()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glUseProgram(program);

    glBindVertexArray(vertexArray);

    glDrawArrays(GL_POINTS, 0, starField.size());
}
