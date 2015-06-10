#include "GLHandler.h"

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

void GLHandler::compileShader(GLuint shaderObj, GLsizei count, const GLchar ** sources, GLint * length)
{
    glShaderSource(shaderObj, count, sources, length);
    glCompileShader(shaderObj);

    GLint status;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint logSize;
        glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &logSize);

        std::vector<char> str(logSize);
        glGetShaderInfoLog(shaderObj, logSize, NULL, &str[0]);
        std::cout << "Shader compilation error:" << std::endl << std::string(str.begin(), str.end()) << std::endl;

        errorState = SHADER_COMPILATION_ERROR;
    }
}

void GLHandler::prepareProgram()
{
    /* Assign our handles a "name" to new shader objects */
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    char vertexSource[] = "\
#version 300 es\n\
\n\
void main(void)\n\
{\n\
gl_Position = vec4(0.0, 0.0, 0.5, 1.0);\n\
}\n\
";
    const GLchar * vertexSourcePtr = vertexSource;
    GLint vertexSourceLength = sizeof(vertexSource);

    char fragmentSource[] = "\
#version 300 es\n\
\n\
out mediump vec4 color;\n\
\n\
void main(void)\n\
{\n\
color = vec4(0.0, 0.8, 1.0, 1.0);\n\
}\n\
";
    const GLchar * fragmentSourcePtr = fragmentSource;
    GLint fragmentSourceLength = sizeof(fragmentSource);

    if (checkState())
        compileShader(vertexShader, 1, &vertexSourcePtr, &vertexSourceLength);

    if (checkState())
        compileShader(fragmentShader, 1, &fragmentSourcePtr, &fragmentSourceLength);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
}

void GLHandler::prepareObjects()
{
    //Create a new VBO and use the variable id to store the VBO id
    glGenVertexArrays(1, &triangleVBO);

    // //Vertices of a triangle (counter-clockwise winding)
    // float data[] = {1.0, 0.0, -0.5, 1.0};

    // //Upload vertex data to the video device
    // glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void GLHandler::resizeWindow(int width, int height)
{
    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
}

void GLHandler::drawGLScene()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //Make the new VBO active
    glBindVertexArray(triangleVBO);

    glUseProgram(program);

    //Actually draw the triangle, giving the number of vertices provided
    glDrawArrays(GL_POINTS, 0, 1);
}
