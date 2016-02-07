#include <cmath>

#include "Quaternion.h"


Quaternion::Quaternion(float w, float x, float y, float z) :
    w(w),
    x(x),
    y(y),
    z(z)
{
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
