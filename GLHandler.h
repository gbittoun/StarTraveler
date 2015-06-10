#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>

#include "ErrorStateBase.h"


class GLHandler : public ErrorStateBase
{
	GLuint program;
    GLuint triangleVBO;

    void prepareObjects();

	void prepareProgram();

	void compileShader(GLuint shaderObj, GLsizei count, const GLchar ** sources, GLint * length);

public:

    GLHandler();

    ErrorCode initGL();

    void resizeWindow(int width, int height);

    void drawGLScene();
};
