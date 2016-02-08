#version 300 es

in mediump vec4 vs_color;

out mediump vec4 color;

void main(void)
{
    mediump float sqrDist = (gl_PointCoord.s - 0.5) * (gl_PointCoord.s - 0.5) + (gl_PointCoord.t - 0.5) * (gl_PointCoord.t - 0.5);
    color.xyz = vs_color.xyz;
    color.w = exp(-20.0*sqrDist);
}
