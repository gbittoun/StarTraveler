#version 300 es

uniform vec4 starPositions[4096];

void main(void)
{
    vec4 position = starPositions[gl_VertexID];
    position.xyz /= 10000.0;
    gl_Position = position;
}
