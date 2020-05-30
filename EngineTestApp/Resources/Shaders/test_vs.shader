#version 420

layout(location = 0) in vec3 in_Position;
out vec3 vPosition;

void main()
{
	vPosition = in_Position.xyz;
}
