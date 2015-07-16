#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>

#include "ErrorStateBase.h"


class ShaderLoader: public ErrorStateBase
{
    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    void compileShader(GLuint shaderObj, GLsizei count, const GLchar ** sources, GLint * length);

    // forbidding copy and assignation
    ShaderLoader(ShaderLoader const &);
    ShaderLoader & operator=(ShaderLoader const &);

public:

    ShaderLoader();
    ~ShaderLoader();

    void setShaderFile(GLenum shaderType, std::string filename);
    ErrorCode generateProgram(GLuint &);
};

#endif
