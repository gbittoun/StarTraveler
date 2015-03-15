#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>

#include "ErrorStateBase.h"


class GLHandler : public ErrorStateBase
{
public:

	GLHandler();

	ErrorCode initGL();

	void resizeWindow(int width, int height);

	void drawGLScene();
};
