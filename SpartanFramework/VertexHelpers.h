#pragma once

namespace SpartanEngine
{
	// A simple vertex with a position and UV coordinate
	struct Vertex2DPosUV
	{
	public:
		Vertex2DPosUV(const Math::Vector2& position, const Math::Vector2& coord) : Position(position), Coord(coord) {}

		Math::Vector2 Position;
		Math::Vector2 Coord;
	};

	struct Vertex2DPosColor
	{
	public:
		Vertex2DPosColor(const Math::Vector2& position, const Math::Color& color) : Position(position), Color(color) {}

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
		Vertex3DPos() : Position(Vector3::Zero()) {}
		Vertex3DPos(const Math::Vector3& position) : Position(position) {}

		Math::Vector3 Position;
	};

	struct Vertex3DPosCoord
	{
	public:
		Vertex3DPosCoord() : Position(Vector3::Zero()), Coord(Vector2::Zero()) {}
		Vertex3DPosCoord(const Math::Vector3& position, const Math::Vector2& coord) : Position(position), Coord(coord) {}

		Math::Vector3 Position;
		Math::Vector2 Coord;
	};

	struct Vertex2DPosColorCoord
	{
	public:
		Vertex2DPosColorCoord(const Math::Vector2& position, const Math::Vector2& coord, const Math::Color& color) : Position(position), Coord(coord), Color(color) {}

		Math::Vector2 Position;
		Math::Vector2 Coord;
		Math::Color Color;
	};

	struct Vertex2DPos
	{
		Vertex2DPos(const Math::Vector2& position) : Position(position) {}

		Math::Vector2 Position;
	};

	struct RawVertex
	{
	public: // Constructors
		RawVertex() : m_VertexData(nullptr) {}
		RawVertex(const std::vector<float>& data) : m_VertexData(new float[data.size()])
		{
			memcpy(m_VertexData, &data[0], data.size() * sizeof(float));
		}
		RawVertex(unsigned int size) : m_VertexData(new float[size]) {}

	public: // Methods
		float& operator[](unsigned int index) { return m_VertexData[index]; }

	public:
		float* m_VertexData;
	};
}