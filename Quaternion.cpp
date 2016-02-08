#include <cmath>

#include "Quaternion.h"


Quaternion::Quaternion(float w, float x, float y, float z) :
    w(w),
    x(x),
    y(y),
    z(z)
{
}

Quaternion Quaternion::operator+(Quaternion const & other)
{
    return Quaternion(this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z);
}

Quaternion Quaternion::operator*(float k)
{
    return Quaternion(this->w * k, this->x * k, this->y * k, this->z * k);
}

Quaternion operator*(float k, Quaternion q)
{
    return q * k;
}

Quaternion Quaternion::operator*(Quaternion const & other)
{
    return Quaternion(
        w * other.w - x * other.x - y * other.y - z * other.z,
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w
    );
}

Quaternion Quaternion::conjugate()
{
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::normalize()
{
    float norm = std::sqrt(w * w + x * x + y * y + z * z);
    return Quaternion(w / norm, x / norm, y / norm, z / norm);
}

std::ostream & operator<<(std::ostream & os, Quaternion q)
{
    os << "Quaternion{" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << "}";

    return os;
}
