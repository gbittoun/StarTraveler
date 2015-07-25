#include <fstream>
#include <sstream>
#include <GL/gl.h>

#include "StarField.h"


std::vector<Star> StarFieldBuilder::fromFile(std::string filename)
{
    std::vector<Star> data;

    std::fstream starFile(filename, std::fstream::in);
    std::string line;
    while (std::getline(starFile, line))
    {
        Star star;

        std::istringstream iss(line);

        float x, y, z, magnitude;
        int color;
        iss >> x;
        iss >> y;
        iss >> z;
        iss >> magnitude;
        iss >> std::hex >> color;

        iss >> std::dec;

        star.position[0] = x;
        star.position[1] = y;
        star.position[2] = z;

        star.magnitude = magnitude;
        star.color[0] = ((GLubyte*)&color)[2];
        star.color[1] = ((GLubyte*)&color)[1];
        star.color[2] = ((GLubyte*)&color)[0];

        data.push_back(star);
    }

    return data;
}
