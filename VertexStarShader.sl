#version 300 es

// Inputs
in vec3 star;
in float magnitude;
in vec3 input_color;

// Outputs
out mediump vec4 vs_color;

// Uniforms
uniform mat4 transformation_matrix;
uniform vec3 camera_position;
uniform vec3 camera_orientation;

// Perspective vars
const float near = 1.0;
const float far = 1000.0;

const float left = -1.0;
const float right = 1.0;

const float top = -1.0;
const float bottom = 1.0;

const mat4 frustum = mat4(
    2.0*near/(right - left)      , 0.0                          , 0.0                           ,  0.0,
    0.0                          , 2.0*near/(top - bottom)      , 0.0                           ,  0.0,
    (right + left)/(right - left), (top + bottom)/(top - bottom), -(far + near)/(far - near)    , -1.0,
    0.0                          , 0.0                          , -2.0*(far * near)/(far - near),  0.0
);

float get_apparent_magnitude(float magnitude, vec3 position)
{
    return magnitude - 5.0 + log(distance(position, vec3(0.0)));
}

float get_point_size_from_apparent_magnitude(float magnitude)
{
    return max(20.0 - 20.0 * magnitude / 1.0, 0.0);
}

void main(void)
{
    gl_PointSize = get_point_size_from_apparent_magnitude(get_apparent_magnitude(magnitude, star));

    vec4 position;
    position.xyz = star - camera_position;
    position.z -= 1.0*(far * near)/(far - near);
    position.w = 1.0;

    gl_Position = frustum * transformation_matrix * position;

    vs_color.xyz = input_color;
    vs_color.w = 1.0;
}
