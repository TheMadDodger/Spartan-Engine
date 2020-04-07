#version 450

uniform mat4 Modelview;
uniform mat3 NormalMatrix;
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in vec3 tePosition[3];
in vec3 tePatchDistance[3];
in float teElevation[3];
out vec3 gNormal;
out vec3 gPatchDistance;
out vec3 gTriDistance;
out float gElevation;
uniform mat4 WorldViewProjection;

void main()
{
    vec3 A = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 B = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    gNormal = NormalMatrix * normalize(cross(A, B));

    gPatchDistance = tePatchDistance[0];
    gTriDistance = vec3(1, 0, 0);
    gElevation = teElevation[0];
    gl_Position = WorldViewProjection * gl_in[0].gl_Position; EmitVertex();

    gPatchDistance = tePatchDistance[1];
    gTriDistance = vec3(0, 1, 0);
    gElevation = teElevation[1];
    gl_Position = WorldViewProjection * gl_in[1].gl_Position; EmitVertex();

    gPatchDistance = tePatchDistance[2];
    gTriDistance = vec3(0, 0, 1);
    gElevation = teElevation[2];
    gl_Position = WorldViewProjection * gl_in[2].gl_Position; EmitVertex();

    EndPrimitive();
}
