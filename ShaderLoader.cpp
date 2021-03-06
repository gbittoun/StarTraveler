#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/glu.h>

#include "ShaderLoader.h"


void ShaderLoader::setShaderFile(GLenum shaderType, std::string filename)
{
    if (checkState())
    {
        std::ifstream t(filename, std::ios::in);
        std::string codeStr;

        if (t.is_open())
            codeStr = std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        else
        {
            std::cout << "Unable to find file \"" << filename << "\"" << std::endl;
            errorState = ErrorStateBase::SHADER_FILE_NOT_FOUND;
        }

        if (checkState())
        {
            if (shaderType == GL_VERTEX_SHADER)
                vertexShaderSource = codeStr;
            if (shaderType == GL_FRAGMENT_SHADER)
                fragmentShaderSource = codeStr;
        }
    }
}

void ShaderLoader::compileShader(GLuint shaderObj, GLsizei count, const GLchar ** sources, GLint * length)
{
    if (checkState())
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

            errorState = ErrorStateBase::SHADER_COMPILATION_ERROR;
        }
    }
}

ErrorStateBase::ErrorCode ShaderLoader::generateProgram(GLuint & program)
{
    if (checkState())
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const GLchar * vertexSourcePtr = vertexShaderSource.c_str();
        GLint vertexSourceLength = vertexShaderSource.size();

        const GLchar * fragmentSourcePtr = fragmentShaderSource.c_str();
        GLint fragmentSourceLength = fragmentShaderSource.size();

        if (checkState())
        {
            std::cout << "Compiling vertex shader" << std::endl;
            compileShader(vertexShader, 1, &vertexSourcePtr, &vertexSourceLength);
        }

        if (checkState())
        {
            std::cout << "Compiling fragment shader" << std::endl;
            compileShader(fragmentShader, 1, &fragmentSourcePtr, &fragmentSourceLength);
        }

        if (checkState())
        {
            program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    return errorState;
}
