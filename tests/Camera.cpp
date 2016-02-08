#include <cmath>

#include <CppUTest/TestHarness.h>

#include "../Camera.h"


TEST_GROUP(CameraTestGroup)
{
};

TEST(CameraTestGroup, CameraConstruction)
{
    Camera camera;

    auto q = camera.getOrientation();

    CHECK_EQUAL(1, q.w);
    CHECK_EQUAL(0, q.x);
    CHECK_EQUAL(0, q.y);
    CHECK_EQUAL(0, q.z);

    auto p = camera.getPosition();

    CHECK_EQUAL(0, p.x);
    CHECK_EQUAL(0, p.y);
    CHECK_EQUAL(0, p.z);
}

TEST(CameraTestGroup, CameraXRotation)
{
    Camera camera;

    camera.updateOrientationXY(1.0, 0.0);

    auto q = camera.getOrientation();

    DOUBLES_EQUAL(std::cos(M_PI * 1.0 / 2), q.w, 1e-15);
    DOUBLES_EQUAL(std::sin(M_PI * 1.0 / 2), q.x, 1e-15);
    DOUBLES_EQUAL(0, q.y, 1e-15);
    DOUBLES_EQUAL(0, q.z, 1e-15);

    Quaternion test(1, 0, 0, 0);

    test = q.conjugate() * Quaternion(0.0, 1.0, 0.0, 0.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-7);
    DOUBLES_EQUAL(1.0, test.x, 1e-7);
    DOUBLES_EQUAL(0.0, test.y, 1e-7);
    DOUBLES_EQUAL(0.0, test.z, 1e-7);

    test = q.conjugate() * Quaternion(0.0, 0.0, 1.0, 0.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-7);
    DOUBLES_EQUAL(0.0, test.x, 1e-7);
    DOUBLES_EQUAL(-1.0, test.y, 1e-7);
    DOUBLES_EQUAL(0.0, test.z, 1e-7);

    test = q.conjugate() * Quaternion(0.0, 0.0, 0.0, 1.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-7);
    DOUBLES_EQUAL(0.0, test.x, 1e-7);
    DOUBLES_EQUAL(0.0, test.y, 1e-7);
    DOUBLES_EQUAL(-1.0, test.z, 1e-7);
}

TEST(CameraTestGroup, CameraYRotation)
{
    Camera camera;

    camera.updateOrientationXY(0.0, 1.0);

    auto q = camera.getOrientation();

    DOUBLES_EQUAL(std::cos(M_PI * 1.0 / 2), q.w, 1e-15);
    DOUBLES_EQUAL(0, q.x, 1e-15);
    DOUBLES_EQUAL(std::sin(M_PI * 1.0 / 2), q.y, 1e-15);
    DOUBLES_EQUAL(0, q.z, 1e-15);

    Quaternion test(1, 0, 0, 0);

    test = q.conjugate() * Quaternion(0.0, 1.0, 0.0, 0.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-7);
    DOUBLES_EQUAL(-1.0, test.x, 1e-7);
    DOUBLES_EQUAL(0.0, test.y, 1e-7);
    DOUBLES_EQUAL(0.0, test.z, 1e-7);

    test = q.conjugate() * Quaternion(0.0, 0.0, 1.0, 0.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-7);
    DOUBLES_EQUAL(0.0, test.x, 1e-7);
    DOUBLES_EQUAL(1.0, test.y, 1e-7);
    DOUBLES_EQUAL(0.0, test.z, 1e-7);

    test = q.conjugate() * Quaternion(0.0, 0.0, 0.0, 1.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-7);
    DOUBLES_EQUAL(0.0, test.x, 1e-7);
    DOUBLES_EQUAL(0.0, test.y, 1e-7);
    DOUBLES_EQUAL(-1.0, test.z, 1e-7);
}

TEST(CameraTestGroup, RotateXThenY)
{
    Camera camera;

    camera.updateOrientationXY(0.5, 0.0);
    camera.updateOrientationXY(0.0, 0.5);

    auto q = camera.getOrientation();

    Quaternion test(1, 0, 0, 0);

    test = q.conjugate() * Quaternion(0.0, 1.0, 0.0, 0.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-6);
    DOUBLES_EQUAL(0.0, test.x, 1e-6);
    DOUBLES_EQUAL(0.0, test.y, 1e-6);
    DOUBLES_EQUAL(1.0, test.z, 1e-6);

    test = q.conjugate() * Quaternion(0.0, 0.0, 1.0, 0.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-6);
    DOUBLES_EQUAL(1.0, test.x, 1e-6);
    DOUBLES_EQUAL(0.0, test.y, 1e-6);
    DOUBLES_EQUAL(0.0, test.z, 1e-6);

    test = q.conjugate() * Quaternion(0.0, 0.0, 0.0, 1.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-6);
    DOUBLES_EQUAL(0.0, test.x, 1e-6);
    DOUBLES_EQUAL(1.0, test.y, 1e-6);
    DOUBLES_EQUAL(0.0, test.z, 1e-6);
}

TEST(CameraTestGroup, RotateYThenX)
{
    Camera camera;

    camera.updateOrientationXY(0.0, 0.5);
    camera.updateOrientationXY(0.5, 0.0);

    auto q = camera.getOrientation();

    Quaternion test(1, 0, 0, 0);

    test = q.conjugate() * Quaternion(0.0, 1.0, 0.0, 0.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-6);
    DOUBLES_EQUAL(0.0, test.x, 1e-6);
    DOUBLES_EQUAL(1.0, test.y, 1e-6);
    DOUBLES_EQUAL(0.0, test.z, 1e-6);

    test = q.conjugate() * Quaternion(0.0, 0.0, 1.0, 0.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-6);
    DOUBLES_EQUAL(0.0, test.x, 1e-6);
    DOUBLES_EQUAL(0.0, test.y, 1e-6);
    DOUBLES_EQUAL(-1.0, test.z, 1e-6);

    test = q.conjugate() * Quaternion(0.0, 0.0, 0.0, 1.0) * q;
    DOUBLES_EQUAL(0.0, test.w, 1e-6);
    DOUBLES_EQUAL(-1.0, test.x, 1e-6);
    DOUBLES_EQUAL(0.0, test.y, 1e-6);
    DOUBLES_EQUAL(0.0, test.z, 1e-6);
}

TEST(CameraTestGroup, RotateXThenTranslate)
{
    Camera camera;

    auto position = camera.getPosition();

    CHECK_EQUAL(0.0, position.x);
    CHECK_EQUAL(0.0, position.y);
    CHECK_EQUAL(0.0, position.z);

    camera.updateOrientationXY(0.5, 0.0);
    camera.updatePositionFromDelta(1.0);

    position = camera.getPosition();

    DOUBLES_EQUAL(0.0, position.x, 1e-6);
    DOUBLES_EQUAL(1.0, position.y, 1e-6);
    DOUBLES_EQUAL(0.0, position.z, 1e-6);
}

TEST(CameraTestGroup, RotateYThenTranslate)
{
    Camera camera;

    auto position = camera.getPosition();

    CHECK_EQUAL(0.0, position.x);
    CHECK_EQUAL(0.0, position.y);
    CHECK_EQUAL(0.0, position.z);

    camera.updateOrientationXY(0.0, 0.5);
    camera.updatePositionFromDelta(1.0);

    position = camera.getPosition();

    DOUBLES_EQUAL(-1.0, position.x, 1e-6);
    DOUBLES_EQUAL(0.0, position.y, 1e-6);
    DOUBLES_EQUAL(0.0, position.z, 1e-6);
}
