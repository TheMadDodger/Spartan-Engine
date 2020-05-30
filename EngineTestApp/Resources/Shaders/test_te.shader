#version 420

#include "SimplexNoise.shader"

layout(triangles, equal_spacing, cw) in;
in vec3 tcPosition[];
out vec3 tePosition;

uniform mat4 WorldViewProjection;

void main()
{
    vec3 p0 = gl_TessCoord.x * tcPosition[0];
    vec3 p1 = gl_TessCoord.y * tcPosition[1];
    vec3 p2 = gl_TessCoord.z * tcPosition[2];
    tePosition = normalize(p0 + p1 + p2);
    float hieght = Evaluate(tePosition, 1.0, 5.0, vec3(0.0, 0.0, 0.0));
    gl_Position = WorldViewProjection * vec4(tePosition * (1.0 + hieght), 1);
}
