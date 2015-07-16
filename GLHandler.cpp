#include "GLHandler.h"
#include "ShaderLoader.h"

#include <vector>


GLHandler::GLHandler() :
	ErrorStateBase()
{
}

GLHandler::~GLHandler()
{
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

void GLHandler::setVertexBuffer(std::vector<GLfloat> const & vertexBufferData)
{
    this->vertexBufferData = vertexBufferData;
}

void GLHandler::prepareObjects()
{
    glUseProgram(program);

    for (auto uniform : uniformMap)
    {
        GLint location = glGetUniformLocation(program, (GLchar*)uniform.first.c_str());
        if (location < 0)
        {
            std::cout << "Couldn’t retrieve location for uniform " << uniform.first << std::endl;
            continue;
        }

        glUniform4fv(location, 4096, &uniform.second[0]);
        if (GL_INVALID_OPERATION == glGetError())
        {
            std::cout << "An error occured while setting values for uniform " << uniform.first << std::endl;
        }
    }

    GLint starLocation = glGetAttribLocation(program, "star");

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertexBufferData.size(), &vertexBufferData[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(starLocation);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);

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

    glDrawArrays(GL_POINTS, 0, vertexBufferData.size() / 3);
}
