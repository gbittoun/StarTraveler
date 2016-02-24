#include <cmath>
#include <cstring>
#include <iostream>

#include "Camera.h"


Camera::Camera() :
    p{0, 0, 0},
    q{1, 0, 0, 0},
    fov(2.5)
{
}

Vector3 Camera::getPosition() const
{
    return this->p;
}

Quaternion Camera::getOrientation() const
{
    return this->q;
}

float Camera::getFOV() const
{
    return this->fov;
}

void Camera::updateOrientationXY(float x, float y)
{
    float norm = std::sqrt(x * x + y * y);

    if (norm == 0.0f)
        return;

    x = x / norm;
    y = y / norm;

    Quaternion result(1.0, 0.0, 0.0, 0.0);

    // Get current X and Y axis in camera referential and get resulting quaternion for this rotation
    {
        auto qx = this->q * Quaternion(0.0, 1.0, 0.0, 0.0) * this->q.conjugate();
        auto qy = this->q * Quaternion(0.0, 0.0, 1.0, 0.0) * this->q.conjugate();

        result = std::cos(M_PI * norm / 2) * Quaternion(1.0, 0.0, 0.0, 0.0) + sin(M_PI * norm / 2) * (x * qx + y * qy);
    }

    this->q = (result * this->q).normalize();
}

void Camera::updatePositionFromDelta(float delta)
{
    Quaternion zAxis(0, 0, 0, -1);
    Quaternion ahead = this->q * zAxis * this->q.conjugate();

    this->p.x += delta * ahead.x;
    this->p.y += delta * ahead.y;
    this->p.z += delta * ahead.z;
}

void Camera::updateFOV(float delta)
{
    fov = std::atan(std::tan(fov - M_PI_2) + delta) + M_PI_2;
}
