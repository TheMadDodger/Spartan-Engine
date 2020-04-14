#version 400

layout(location = 0) out vec4 out_Color;

in vec2 in_TexCoord;

uniform sampler2D UITexture;

void main()
{
	out_Color = texture2D(UITexture, in_TexCoord);
}