#version 420

layout(location = 0) out vec4 out_Color;

uniform vec4 Color = vec4(0, 1, 0, 1);

void main()
{
    out_Color = Color;
}