#version 300 es

// Inputs
in vec3 star;
in float magnitude;
in vec3 input_color;

// Outputs
out mediump vec4 vs_color;

// Uniforms
uniform vec3 camera_position;
uniform vec4 camera_orientation;
uniform float camera_fov;

// Perspective vars
const float near = 0.000001;
const float far = 1000000.0;

vec4 quat_mult(vec4 q1, vec4 q2)
{
    vec4 qr;
    qr.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
    qr.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
    qr.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
    qr.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);

    return qr;
}

vec4 quat_conjugate(vec4 q)
{
    vec4 qr;
    qr.w = q.w;
    qr.xyz = -q.xyz;

    return qr;
}

vec3 rotate(vec3 p, vec4 q)
{
    vec4 qv;
    qv.w = 0.0;
    qv.xyz = p.xyz;

    qv = quat_mult(quat_conjugate(q), quat_mult(qv, q));

    return qv.xyz;
}

vec3 apply_frustum(vec3 position)
{
    vec3 result = position;

    float a = 2.0 / (far - near);
    float b = -1.0 - a * near;

    result.z = a * result.z + b;

    a = ((far - near) * cos(camera_fov / 2.0));
    b = near * cos(camera_fov / 2.0) + a;

    result.x = result.x / (a * result.z + b);
    result.y = result.y / (a * result.z + b);

    return result;
}

float get_apparent_magnitude(float magnitude, vec3 position)
{
    return 5.0 * log(distance(position, vec3(0.0)) * 0.30659458) / log(10.0) + magnitude;
}

void main(void)
{
    vec3 position = star;

    position = position - camera_position;
    position = rotate(position, camera_orientation);

    float apparent_magnitude = get_apparent_magnitude(magnitude, position);

    gl_PointSize = 20.0 / (1.0 + exp(1.0 * (apparent_magnitude - 9.0)));  // Sigmoid is the best way to compute stars diameter

    position = apply_frustum(position);

    gl_Position.xyz = position.xyz;
    gl_Position.w = 1.0;

    vs_color.xyz = input_color;
    vs_color.w = 1.0;
}
