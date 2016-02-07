#include <cmath>
#include <cstring>

#include "Camera.h"


Camera::Camera() :
    p{0, 0, 0},
    q{1, 0, 0, 0}
{
}

void Camera::getPosition(float output[3])
{
    memcpy(output, this->p, sizeof(this->p));
}

Quaternion Camera::getOrientation()
{
    return this->q;
}

void Camera::updateOrientationXY(float x, float y)
{
    this->q = this->q * Quaternion(std::cos(x), std::sin(x), 0, 0);
    this->q = this->q * Quaternion(std::cos(y), 0, std::sin(y), 0);

    this->q = this->q.normalize();
}

void Camera::updatePositionFromDelta(float delta)
{
    Quaternion zAxis(0, 0, 0, -1);
    Quaternion ahead = this->q * zAxis * this->q.conjugate();

    this->p[0] += delta * ahead.x;
    this->p[1] += delta * ahead.y;
    this->p[2] += delta * ahead.z;
}
