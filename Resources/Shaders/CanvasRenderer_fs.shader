#version 400

in vec2 Coord;
out vec4 out_Color;
uniform sampler2D CanvasTexture;

void main()
{
	out_Color = texture2D(CanvasTexture, Coord);
}