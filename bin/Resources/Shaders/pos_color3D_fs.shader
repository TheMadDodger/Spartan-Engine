#version 400

layout(location = 0) out vec4 out_Color;

in vec4 Color;

void main()
{
	out_Color = Color;
}