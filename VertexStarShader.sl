#version 300 es

in vec3 star;
in float magnitude;
in vec3 input_color;

uniform mat4 view_matrix;

out mediump vec4 vs_color;

vec4 apply_view_matrix(vec4 obj)
{
    return view_matrix * obj;
}

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
    gl_Position.xyz = star / 1000.0;
    gl_Position.w = 1.0;
    gl_PointSize = get_point_size_from_apparent_magnitude(get_apparent_magnitude(magnitude, star));
    //gl_PointSize = magnitude * 10.0;

    vs_color.xyz = input_color;
    vs_color.w = 1.0;
}
