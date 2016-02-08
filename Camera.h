#pragma once

#include "Vector3.h"
#include "Quaternion.h"


class Camera
{
    Vector3 p;
    Quaternion q;

public:

    Camera();

    Vector3 getPosition() const;

    Quaternion getOrientation() const;

    void updateOrientationXY(float x, float y);

    void updatePositionFromDelta(float);
};
