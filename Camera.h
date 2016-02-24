#pragma once

#include "Vector3.h"
#include "Quaternion.h"


class Camera
{
    Vector3 p;
    Quaternion q;
    float fov;

public:

    Camera();

    Vector3 getPosition() const;

    Quaternion getOrientation() const;

    float getFOV() const;

    void updateOrientationXY(float x, float y);

    void updatePositionFromDelta(float);

    void updateFOV(float);
};
