#version 300 es

in vec3 star;

void main(void)
{
    gl_Position.xyz = star / 10.0;
    gl_Position.w = 1.0;
}
