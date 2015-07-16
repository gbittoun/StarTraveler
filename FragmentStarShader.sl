#version 300 es

in mediump vec4 vertexColor;

out mediump vec4 color;

void main(void)
{
    mediump float sqrDist = (gl_PointCoord.s - 0.5) * (gl_PointCoord.s - 0.5) + (gl_PointCoord.t - 0.5) * (gl_PointCoord.t - 0.5);
	color = vec4(0.0, 1.0, 1.0, exp(-100.0*sqrDist));
}
