#version 400

layout(location = 0) in vec3 in_Position;

out vec4 Color;
uniform mat4 WorldViewProjection = mat4(1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);

void main()
{
	gl_Position = WorldViewProjection * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	Color = vec4(clamp(in_Position, 0.0, 1.0), 1.0);
}
