#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "ErrorStateBase.h"
#include "StarField.h"


class GLHandler : public ErrorStateBase
{
	GLuint program;
    GLuint vertexBuffer;
    GLuint vertexArray;

    std::map<std::string, std::vector<GLfloat> > uniformMap;
    std::vector<Star> starField;

    void prepareObjects();

	void prepareProgram();

    // forbidding copy and assignation
    GLHandler(GLHandler const &);
    GLHandler & operator=(GLHandler const &);

public:

    GLHandler();
    ~GLHandler();

    ErrorCode initGL();

    void resizeWindow(int width, int height);

    void drawGLScene();

    void setUniform(std::string const &, std::vector<GLfloat> const &);

    void setStarField(std::vector<Star> const &);

    void rotatePOV();
};
