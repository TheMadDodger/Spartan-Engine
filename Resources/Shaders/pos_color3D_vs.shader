#version 400

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;

out vec4 Color;
uniform mat4 WorldViewProjection = mat4(1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);

void main()
{
	gl_Position = WorldViewProjection * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	Color = in_Color;
}
