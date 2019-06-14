#pragma once
#include "stdafx.h"
#include "VertexHelpers.h"

enum Mesh2DAttribute
{
	APosition2D,
	AColor,
	ACoord,
};

class Mesh2D
{
public:
	Mesh2D(size_t vertexCount, float *pVertices, size_t indexCount, unsigned int *pIndices, size_t vertexSize, size_t attributeCount, Mesh2DAttribute *attributes) :
		m_VertexCount(vertexCount), m_pVertices(pVertices), m_IndexCount(indexCount), m_pIndices(pIndices), m_VertexSize(vertexSize), m_AttributeCount(attributeCount), m_Attributes(attributes) {}
	virtual ~Mesh2D()
	{
		if (m_IsMeshBuilt)
		{
			glBindVertexArray(m_VertexArrayID);
			Utilities::Debug::LogGLError(glGetError());
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
			Utilities::Debug::LogGLError(glGetError());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
			Utilities::Debug::LogGLError(glGetError());

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			Utilities::Debug::LogGLError(glGetError());
			glDeleteBuffers(1, &m_IndexBufferID);
			Utilities::Debug::LogGLError(glGetError());

			for (int i = m_AttributeCount - 1; i >= 0; --i)
			{
				glDisableVertexAttribArray(i);
				Utilities::Debug::LogGLError(glGetError());
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			Utilities::Debug::LogGLError(glGetError());
			glDeleteBuffers(1, &m_VertexBufferID);
			Utilities::Debug::LogGLError(glGetError());

			glBindVertexArray(0);
			Utilities::Debug::LogGLError(glGetError());
			glDeleteVertexArrays(1, &m_VertexArrayID);
			Utilities::Debug::LogGLError(glGetError());
		}
	}

	// Creates the buffers and binds its attributes
	void BuildMesh()
	{
		if (m_IsMeshBuilt) return;

		// Generate vertex array
		//glGenVertexArrays(1, &m_VertexArrayID);
		//Utilities::Debug::LogGLError(glGetError());

		// Bind this new vertex array
		//glBindVertexArray(m_VertexArrayID);
		//Utilities::Debug::LogGLError(glGetError());

		// Generate the vertex buffer
		glGenBuffersARB(1, &m_VertexBufferID);
		Utilities::Debug::LogGLError(glGetError());
		// Generate the index buffer
		glGenBuffersARB(1, &m_IndexBufferID);
		Utilities::Debug::LogGLError(glGetError());

		// Bind the vertex buffer
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VertexBufferID);
		Utilities::Debug::LogGLError(glGetError());
		// Copy data to buffer
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(m_pVertices), m_pVertices, GL_STATIC_DRAW_ARB);
		Utilities::Debug::LogGLError(glGetError());
		// Unbind the buffer
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		Utilities::Debug::LogGLError(glGetError());

		// Bind index buffer
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexBufferID);
		Utilities::Debug::LogGLError(glGetError());
		// Copy data to buffer
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(m_pIndices), m_pIndices, GL_STATIC_DRAW_ARB);
		Utilities::Debug::LogGLError(glGetError());
		// Unbind the buffer
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
		Utilities::Debug::LogGLError(glGetError());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VertexBufferID);
		glVertexPointer(2, GL_FLOAT, sizeof(Vertex2DPosColor), MEMBER_OFFSET)

		/*size_t offset = 0;
		for (size_t i = 0; i < m_AttributeCount; i++)
		{
			glEnableVertexAttribArray(i);
			Utilities::Debug::LogGLError(glGetError());

			Mesh2DAttribute attribute = m_Attributes[i];

			switch (attribute)
			{
			case AColor:
				glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, m_VertexSize, (void*)offset);
				Utilities::Debug::LogGLError(glGetError());
				offset += 4 * sizeof(float);
				break;
			case APosition2D:
			case ACoord:
				glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, m_VertexSize, (void*)offset);
				Utilities::Debug::LogGLError(glGetError());
				offset += 2 * sizeof(float);
				break;
			default:
				Utilities::Debug::LogWarning("Mesh::BuildMesh > This attribute type is not yet supported.");
				break;
			}
		}*/

		// Create index buffer
		/*glGenBuffers(1, &m_IndexBufferID);
		Utilities::Debug::LogGLError(glGetError());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		Utilities::Debug::LogGLError(glGetError());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(int), m_pIndices, GL_STATIC_DRAW);
		Utilities::Debug::LogGLError(glGetError());

		// Unbind buffers
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		Utilities::Debug::LogGLError(glGetError());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Utilities::Debug::LogGLError(glGetError());
		glBindVertexArray(0);
		Utilities::Debug::LogGLError(glGetError());*/

		m_IsMeshBuilt = true;
	}

	const GLuint GetVertexArrayID() const
	{
		if (!m_IsMeshBuilt) return 0;
		return m_VertexArrayID;
	}

	const size_t GetIndexCount() const
	{
		return m_IndexCount;
	}

	const size_t GetVertexCount() const
	{
		return m_VertexCount;
	}

	const size_t GetVertexSize() const
	{
		return m_VertexSize;
	}

private:
	bool m_IsMeshBuilt = false;
	float *m_pVertices = nullptr;
	unsigned int *m_pIndices = nullptr;
	size_t m_VertexCount;
	size_t m_IndexCount;
	GLuint m_VertexBufferID;
	GLuint m_VertexArrayID;
	GLuint m_IndexBufferID;

	size_t m_VertexSize;
	size_t m_AttributeCount;
	Mesh2DAttribute *m_Attributes;
};

class MeshHelper
{
public:
	static Mesh2D *Generate2DBoxMeshPosColor(const Math::Vector2 &halfSize, const Color &color)
	{
		// Vertex array
		Vertex2DPosColor vertices[4] =
		{
			Vertex2DPosColor(Vector2(-halfSize.x, halfSize.y), color), // TopLeft
			Vertex2DPosColor(Vector2(halfSize.x, halfSize.y), color), // TopRight
			Vertex2DPosColor(Vector2(-halfSize.x, -halfSize.y), color), // BottomLeft
			Vertex2DPosColor(Vector2(halfSize.x, -halfSize.y), color), // BottomRight
		};

		// Index array
		unsigned int indices[6] =
		{
			2, 0, 3,
			1, 3, 0,
		};

		// Attribute array
		Mesh2DAttribute attributes[] =
		{
			Mesh2DAttribute::APosition2D,
			Mesh2DAttribute::AColor,
		};

		// Create the mesh
		Mesh2D *pMesh = new Mesh2D((size_t)4, (float*)vertices, (size_t)6, indices, sizeof(Vertex2DPosUV), (size_t)2, attributes);

		// Build the mesh
		pMesh->BuildMesh();

		// Return mesh
		return pMesh;
	}

	static Mesh2D *Generate2DBoxMeshPosCoord(const Math::Vector2 &halfSize)
	{
		// Vertex array
		Vertex2DPosUV vertices[4] =
		{
			Vertex2DPosUV(Vector2(-halfSize.x, halfSize.y), Vector2(0.0f, 0.0f)), // TopLeft
			Vertex2DPosUV(Vector2(halfSize.x, halfSize.y), Vector2(1.0f, 0.0f)), // TopRight
			Vertex2DPosUV(Vector2(-halfSize.x, -halfSize.y), Vector2(0.0f, 1.0f)), // BottomLeft
			Vertex2DPosUV(Vector2(halfSize.x, -halfSize.y), Vector2(1.0f, 1.0f)), // BottomRight
		};

		// Index array
		unsigned int indices[6] = 
		{
			2, 0, 3,
			1, 3, 0,
		};

		// Attribute array
		Mesh2DAttribute attributes[] = 
		{
			Mesh2DAttribute::APosition2D,
			Mesh2DAttribute::ACoord,
		};

		// Create the mesh
		Mesh2D *pMesh = new Mesh2D((size_t)4, (float*)vertices, (size_t)6, indices, sizeof(Vertex2DPosUV), (size_t)2, attributes);

		// Build the mesh
		pMesh->BuildMesh();

		// Return mesh
		return pMesh;
	}

private:
	MeshHelper();
	~MeshHelper();
};
