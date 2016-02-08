#pragma once

#include <iostream>


struct Quaternion
{
    float w, x, y, z;

    Quaternion(float w, float x, float y, float z);

    Quaternion operator+(Quaternion const &);

    Quaternion operator*(Quaternion const &);

    Quaternion operator*(float);

    Quaternion conjugate();

    Quaternion normalize();

    friend Quaternion operator*(float k, Quaternion q);

    friend std::ostream & operator<<(std::ostream & os, Quaternion q);
};
