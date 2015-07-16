#version 300 es

out vec4 color;

in vec3 star;

void main(void)
{
    gl_Position.xyz = star / 1000.0;
    gl_Position.w = 1.0;
    gl_PointSize = 10.0 / (star.z + 0.01);

    color = vec4(0.0, 0.5, 0.5, 0.5);
}
