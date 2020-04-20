#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 out_TexCoord;

uniform mat4 WorldProjection;
uniform vec4 CenterOffsets;

void main()
{
	vec4 pivot = gl_in[0].gl_Position;

	float left = CenterOffsets.x;
	float top = CenterOffsets.y;
	float right = CenterOffsets.z;
	float bottom = CenterOffsets.w;

	// Bottom left
	gl_Position = pivot;
	gl_Position.x += left;
	gl_Position.y += bottom;
	gl_Position = WorldProjection * gl_Position;
	out_TexCoord = vec2(0.0, 0.0);
	EmitVertex();

	// Bottom right
	gl_Position = pivot;
	gl_Position.x += right;
	gl_Position.y += bottom;
	gl_Position = WorldProjection * gl_Position;
	out_TexCoord = vec2(1.0, 0.0);
	EmitVertex();

	// Top left
	gl_Position = pivot;
	gl_Position.x += left;
	gl_Position.y += top;
	gl_Position = WorldProjection * gl_Position;
	out_TexCoord = vec2(0.0, 1.0);
	EmitVertex();

	// Top right
	gl_Position = pivot;
	gl_Position.x += right;
	gl_Position.y += top;
	gl_Position = WorldProjection * gl_Position;
	out_TexCoord = vec2(1.0, 1.0);
	EmitVertex();

	EndPrimitive();
}