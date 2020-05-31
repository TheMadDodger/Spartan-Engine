#version 420

layout(location = 0) in vec3 in_Position;

uniform mat4 WorldViewProjection;

void main()
{
	gl_Position = WorldViewProjection * vec4(in_Position, 1.0);
}
