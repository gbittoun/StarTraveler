#pragma once

#include <vector>


struct Star
{
    GLfloat position[3];
    GLfloat magnitude;
    GLubyte color[3];
};

class StarFieldBuilder
{
public:

    std::vector<Star> fromFile(std::string filename);
};
