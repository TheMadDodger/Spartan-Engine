#version 400

in vec2 Coord;
out vec4 out_Color;
uniform sampler2D ScreenTexture;

void main()
{
	out_Color = texture2D(ScreenTexture, Coord);
}