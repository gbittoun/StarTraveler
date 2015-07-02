#include "GLHandler.h"
#include "ShaderLoader.h"

#include <vector>


GLHandler::GLHandler() :
	ErrorStateBase()
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
    ShaderLoader loader = ShaderLoader();
    loader.setShaderFile(GL_VERTEX_SHADER, "VertexStarShader.sl");
    loader.setShaderFile(GL_FRAGMENT_SHADER, "FragmentStarShader.sl");

    errorState = loader.generateProgram(program);
}

void GLHandler::setUniform(std::string const & uniformName, std::vector<GLfloat> const & values)
{
    uniformMap[uniformName] = values;
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

    //Actually draw the triangle, giving the number of vertices provided
    glDrawArrays(GL_POINTS, 0, 4096);
}
