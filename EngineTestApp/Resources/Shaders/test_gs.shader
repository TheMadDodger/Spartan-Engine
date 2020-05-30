#version 450

uniform mat4 Modelview;
uniform mat3 NormalMatrix;
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in vec3 tePosition[3];
in float teElevation[3];
out vec3 gNormal;
out float gElevation;
out vec3 gFragPos;
uniform mat4 WorldViewProjection;
uniform mat4 WorldMatrix;

void main()
{
    vec3 A = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 B = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    //vec3 A = tePosition[2] - tePosition[0];
    //vec3 B = tePosition[1] - tePosition[0];
    gNormal = NormalMatrix * normalize(cross(A, B));

    gElevation = teElevation[0];
    gl_Position = WorldViewProjection * gl_in[0].gl_Position;
    gFragPos = (WorldMatrix * gl_in[0].gl_Position).xyz; EmitVertex();

    gElevation = teElevation[1];
    gl_Position = WorldViewProjection * gl_in[1].gl_Position;
    gFragPos = (WorldMatrix * gl_in[1].gl_Position).xyz; EmitVertex();

    gElevation = teElevation[2];
    gl_Position = WorldViewProjection * gl_in[2].gl_Position;
    gFragPos = (WorldMatrix * gl_in[2].gl_Position).xyz; EmitVertex();

    EndPrimitive();
}
