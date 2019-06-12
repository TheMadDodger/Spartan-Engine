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
