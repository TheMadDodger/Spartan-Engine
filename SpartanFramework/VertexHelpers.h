#pragma once
#include "stdafx.h"

// A simple vertex with a position and UV coordinate
struct Vertex2DPosUV
{
public:
	Vertex2DPosUV(const Math::Vector2 &position, const Math::Vector2 &coord) : Position(position), Coord(coord) {}

	Math::Vector2 Position;
	Math::Vector2 Coord;
};

struct Vertex2DPosColor
{
public:
	Vertex2DPosColor(const Math::Vector2 &position, const Math::Color &color) : Position(position), Color(color) {}

	Math::Vector2 Position;
	Math::Color Color;
};

struct Vertex3DPosColor
{
public:
	Vertex3DPosColor(const Math::Vector3& position, const Math::Color& color) : Position(position), Color(color) {}

	Math::Vector3 Position;
	Math::Color Color;
};

struct Vertex3DPos
{
public:
	Vertex3DPos(const Math::Vector3& position) : Position(position) {}

	Math::Vector3 Position;
};

struct Vertex2DPosColorCoord
{
public:
	Vertex2DPosColorCoord(const Math::Vector2 &position, const Math::Vector2 &coord, const Math::Color &color) : Position(position), Coord(coord), Color(color) {}

	Math::Vector2 Position;
	Math::Vector2 Coord;
	Math::Color Color;
};

struct Vertex2DPos
{
	Vertex2DPos(const Math::Vector2 &position) : Position(position) {}

	Math::Vector2 Position;
};

struct SuperVertex3D
{
	Math::Vector3 Position;
	Math::Vector3 Normal;
	Math::Vector3 Tangent;
	Math::Vector2 Coord;
	Math::Color Color;
};