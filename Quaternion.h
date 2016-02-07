#pragma once

struct Quaternion
{
    float w, x, y, z;

    Quaternion(float w, float x, float y, float z);

    Quaternion operator*(Quaternion const &);

    Quaternion conjugate();

    Quaternion normalize();
};