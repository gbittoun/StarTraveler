#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "ErrorStateBase.h"


class GLHandler : public ErrorStateBase
{
	GLuint program;

    std::map<std::string, std::vector<GLfloat> > uniformMap;

    void prepareObjects();

	void prepareProgram();

public:

    GLHandler();

    ErrorCode initGL();

    void resizeWindow(int width, int height);

    void drawGLScene();

    void setUniform(std::string const &, std::vector<GLfloat> const &);
};
