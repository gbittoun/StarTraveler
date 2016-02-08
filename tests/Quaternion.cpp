#include <cmath>

#include <CppUTest/TestHarness.h>

#include "../Quaternion.h"


TEST_GROUP(QuaternionTestGroup)
{
};

TEST(QuaternionTestGroup, NeutralQuaternion)
{
    Quaternion q(1, 0, 0, 0);
    Quaternion v1(0, 1, 2, 3);
    Quaternion v2(1, 0, 0, 0);

    v2 = q * v1;
    CHECK_EQUAL(v1.w, v2.w);
    CHECK_EQUAL(v1.x, v2.x);
    CHECK_EQUAL(v1.y, v2.y);
    CHECK_EQUAL(v1.z, v2.z);

    v2 = v1 * q;
    CHECK_EQUAL(v1.w, v2.w);
    CHECK_EQUAL(v1.x, v2.x);
    CHECK_EQUAL(v1.y, v2.y);
    CHECK_EQUAL(v1.z, v2.z);
}

TEST(QuaternionTestGroup, XRotateQuaternion)
{
    Quaternion q(1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0), 0, 0);
    Quaternion v1(0, 1, 2, 3);
    Quaternion v2(0, 0, 0, 0);

    v2 = q * v1 * q.conjugate();   // pi/2 rotation on x
    DOUBLES_EQUAL(v1.w, v2.w, 1e-6);
    DOUBLES_EQUAL(v1.x, v2.x, 1e-6);
    DOUBLES_EQUAL(v1.y, v2.z, 1e-6);
    DOUBLES_EQUAL(v1.z, -v2.y, 1e-6);
}

TEST(QuaternionTestGroup, YRotateQuaternion)
{
    Quaternion q(1.0 / std::sqrt(2.0), 0, 1.0 / std::sqrt(2.0), 0);
    Quaternion v1(0, 1, 2, 3);
    Quaternion v2(0, 0, 0, 0);

    v2 = q * v1 * q.conjugate();  // pi/2 rotation on y
    DOUBLES_EQUAL(v1.w, v2.w, 1e-6);
    DOUBLES_EQUAL(v1.x, -v2.z, 1e-6);
    DOUBLES_EQUAL(v1.y, v2.y, 1e-6);
    DOUBLES_EQUAL(v1.z, v2.x, 1e-6);
}

TEST(QuaternionTestGroup, ZRotateQuaternion)
{
    Quaternion q(1.0 / std::sqrt(2.0), 0, 0, 1.0 / std::sqrt(2.0));
    Quaternion v1(0, 1, 2, 3);
    Quaternion v2(0, 0, 0, 0);

    v2 = q * v1 * q.conjugate();  // pi/2 rotation on z
    DOUBLES_EQUAL(v1.w, v2.w, 1e-6);
    DOUBLES_EQUAL(v1.x, v2.y, 1e-6);
    DOUBLES_EQUAL(v1.y, -v2.x, 1e-6);
    DOUBLES_EQUAL(v1.z, v2.z, 1e-6);
}

TEST(QuaternionTestGroup, QuaternionNormalization)
{
    Quaternion q(1, 2, 3, 4);

    q = q.normalize();

    DOUBLES_EQUAL(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z, 1.0, 1e-6);
}
