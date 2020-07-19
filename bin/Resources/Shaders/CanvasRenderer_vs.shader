#version 400

layout(location = 0) in vec3 in_Position;

out vec2 Coord;
uniform mat4 CanvasProjectionMat;

void main()
{
	Coord = vec2(clamp(in_Position.x, 0.0, 1.0), clamp(in_Position.y, 0.0, 1.0));
	gl_Position = CanvasProjectionMat * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
}