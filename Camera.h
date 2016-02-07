#pragma once

#include "Quaternion.h"


class Camera
{
    float p[3];
    Quaternion q;

public:

    Camera();

    void getPosition(float[3]);

    Quaternion getOrientation();

    void updateOrientationXY(float x, float y);

    void updatePositionFromDelta(float);
};
