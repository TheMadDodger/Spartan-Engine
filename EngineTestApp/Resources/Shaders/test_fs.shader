#version 420

layout(location = 0) out vec4 out_Color;

layout(std140, binding = 0) uniform TestBlock
{
	vec4[12] Colors;
} _Test;

void main()
{
	int colorIndex = gl_PrimitiveID % 12;
	out_Color = _Test.Colors[colorIndex];
}