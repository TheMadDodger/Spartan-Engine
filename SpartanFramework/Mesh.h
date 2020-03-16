#pragma once
#include "stdafx.h"
#include "VertexHelpers.h"
#include "SEObject.h"

#define MEMBER_OFFSET(s,m) ((char *)NULL + (offsetof(s,m)))
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

enum MeshAttribute : unsigned int
{
	APosition2D,
	APosition3D,
	ANormal,
	ATangent,
	AColor,
	ACoord,
	ABiNormal,
};

class Mesh : public SEObject
{
public:
	Mesh(size_t vertexCount, float *pVertices, size_t indexCount, unsigned int *pIndices, size_t vertexSize, size_t attributeCount, MeshAttribute *attributes, GLuint primitiveTopology = GL_TRIANGLE_FAN) :
		m_VertexCount(vertexCount), m_pVertices(pVertices),
		m_IndexCount(indexCount), m_pIndices(pIndices),
		m_VertexSize(vertexSize), m_AttributeCount(attributeCount),
		m_pAttributes(new MeshAttribute[m_AttributeCount]), m_PrimitiveTopoloy(primitiveTopology),
		m_IndexBufferID(NULL), m_VertexBufferID(NULL)
	{
		memcpy(m_pAttributes, attributes, m_AttributeCount * sizeof(unsigned int));
	}

	virtual ~Mesh()
	{
		if (m_IsMeshBuilt)
		{
			glDeleteBuffers(1, &m_IndexBufferID);
			Utilities::Debug::LogGLError(glGetError());
			glDeleteBuffers(1, &m_VertexBufferID);
			Utilities::Debug::LogGLError(glGetError());
		}

		delete[] m_pAttributes;
	}

	// Creates the buffers and binds its attributes
	void BuildMesh()
	{
		if (m_IsMeshBuilt) return;

		//Create VBO
		glGenBuffers(1, &m_VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, m_VertexSize * m_VertexCount, m_pVertices, GL_STATIC_DRAW);

		//Create IBO
		glGenBuffers(1, &m_IndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(GLuint), m_pIndices, GL_STATIC_DRAW);

		m_IsMeshBuilt = true;
	}

	const GLuint GetVertexBufferID() const
	{
		if (!m_IsMeshBuilt) return 0;
		return m_VertexBufferID;
	}

	const GLuint GetIndexBufferID() const
	{
		if (!m_IsMeshBuilt) return 0;
		return m_IndexBufferID;
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

	void SetPrimitiveTopology(GLuint topology)
	{
		m_PrimitiveTopoloy = topology;
	}

private:
	friend class MeshRenderComponent;

	void ApplyAttributes()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);

		size_t offset = 0;
		for (size_t i = 0; i < m_AttributeCount; i++)
		{
			glEnableVertexAttribArray(i);
			Utilities::Debug::LogGLError(glGetError());

			MeshAttribute attribute = m_pAttributes[i];

			switch (attribute)
			{
			case AColor:
				glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, m_VertexSize, (void*)offset);
				Utilities::Debug::LogGLError(glGetError());
				offset += 4 * sizeof(GLfloat);
				break;
			case APosition2D:
			case ACoord:
				glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, m_VertexSize, (void*)offset);
				Utilities::Debug::LogGLError(glGetError());
				offset += 2 * sizeof(GLfloat);
				break;
			case ATangent:
			case ABiNormal:
			case ANormal:
			case APosition3D:
				glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, m_VertexSize, (void*)offset);
				Utilities::Debug::LogGLError(glGetError());
				offset += 3 * sizeof(GLfloat);
				break;
			default:
				Utilities::Debug::LogWarning("Mesh::BuildMesh > This attribute type is not yet supported.");
				break;
			}
		}

		// Set index data and render
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	}

	void Draw()
	{
		glDrawElements(m_PrimitiveTopoloy, m_IndexCount, GL_UNSIGNED_INT, NULL);
	}

	void DrawEnd()
	{
		// Disable attributes
		for (size_t i = 0; i < m_AttributeCount; i++)
		{
			glDisableVertexAttribArray(i);
		}

		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	}

private:
	bool m_IsMeshBuilt = false;
	float *m_pVertices = nullptr;
	unsigned int *m_pIndices = nullptr;
	size_t m_VertexCount;
	size_t m_IndexCount;
	GLuint m_VertexBufferID;
	GLuint m_IndexBufferID;
	GLuint m_PrimitiveTopoloy;

	size_t m_VertexSize;
	size_t m_AttributeCount;
	MeshAttribute *m_pAttributes;
};

class MeshHelper : SEObject
{
public:
	static Mesh *Generate2DBoxMeshPosColor(const Math::Vector2 &halfSize, const Color &color)
	{
		//VBO data
		Vertex2DPosColor vertexData[] =
		{
			Vertex2DPosColor(Vector2(-halfSize.x, -halfSize.y), color),
			Vertex2DPosColor(Vector2(halfSize.x, -halfSize.y), color),
			Vertex2DPosColor(Vector2(halfSize.x, halfSize.y), color),
			Vertex2DPosColor(Vector2(-halfSize.x,  halfSize.y), color)
		};

		//IBO data
		GLuint indexData[] = { 0, 1, 2, 3 };

		MeshAttribute attributes[] =
		{
			MeshAttribute::APosition2D,
			MeshAttribute::AColor,
		};

		Mesh *pMesh = new Mesh(4, (float*)vertexData, 4, indexData, sizeof(Vertex2DPosColor), 2, attributes);
		pMesh->BuildMesh();

		// Return mesh
		return pMesh;
	}

	static Mesh* Generate3DBoxMeshPosColor(const Math::Vector3& halfSize, const Color& color1, const Color& color2, const Color& color3, const Color& color4, const Color& color5, const Color& color6)
	{
		//VBO data
		Vertex3DPos vertexData[] =
		{
			Vertex3DPos(Vector3(-halfSize.x, -halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, -halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(-halfSize.x,  halfSize.y, -halfSize.z)),

			Vertex3DPos(Vector3(-halfSize.x, -halfSize.y, halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, -halfSize.y, halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, halfSize.y, halfSize.z)),
			Vertex3DPos(Vector3(-halfSize.x,  halfSize.y, halfSize.z)),

			Vertex3DPos(Vector3(-halfSize.x, halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, halfSize.y, halfSize.z)),
			Vertex3DPos(Vector3(-halfSize.x,  halfSize.y, halfSize.z)),

			Vertex3DPos(Vector3(-halfSize.x, -halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, -halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, -halfSize.y, halfSize.z)),
			Vertex3DPos(Vector3(-halfSize.x,  -halfSize.y, halfSize.z)),

			Vertex3DPos(Vector3(-halfSize.x, -halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(-halfSize.x, halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(-halfSize.x, halfSize.y, halfSize.z)),
			Vertex3DPos(Vector3(-halfSize.x,  -halfSize.y, halfSize.z)),

			Vertex3DPos(Vector3(halfSize.x, -halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, halfSize.y, -halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x, halfSize.y, halfSize.z)),
			Vertex3DPos(Vector3(halfSize.x,  -halfSize.y, halfSize.z))
		};

		//IBO data
		GLuint indexData[] = { 0, 1, 2, 2, 0, 3, 4, 5, 6, 6, 4, 7, 8, 9, 10, 10, 8, 11, 12, 13, 14, 14, 12, 15, 16, 17, 18, 18, 16, 19, 20, 21, 22, 22, 20, 23, };

		MeshAttribute attributes[] =
		{
			MeshAttribute::APosition3D,
		};

		Mesh* pMesh = new Mesh(24, (float*)vertexData, 36, indexData, sizeof(Vertex3DPos), 1, attributes, GL_TRIANGLES);
		pMesh->BuildMesh();

		// Return mesh
		return pMesh;
	}

	static Mesh *Generate2DBoxMeshPosColorCoord(const Math::Vector2 &halfSize, const Color &color)
	{
		//VBO data
		Vertex2DPosColorCoord vertexData[] =
		{
			Vertex2DPosColorCoord(Vector2(-halfSize.x, -halfSize.y), Vector2(0.0f, 0.0f), color),
			Vertex2DPosColorCoord(Vector2(halfSize.x, -halfSize.y), Vector2(1.0f, 0.0f), color),
			Vertex2DPosColorCoord(Vector2(halfSize.x, halfSize.y), Vector2(1.0f, 1.0f), color),
			Vertex2DPosColorCoord(Vector2(-halfSize.x,  halfSize.y), Vector2(0.0f, 1.0f), color)
		};

		//IBO data
		GLuint indexData[] = { 0, 1, 2, 3 };

		MeshAttribute attributes[] =
		{
			MeshAttribute::APosition2D,
			MeshAttribute::ACoord,
			MeshAttribute::AColor,
		};

		Mesh *pMesh = new Mesh(4, (float*)vertexData, 4, indexData, sizeof(Vertex2DPosColorCoord), 3, attributes);
		pMesh->BuildMesh();

		// Return mesh
		return pMesh;
	}

	static Mesh *Generate2DBoxMeshPosCoord(const Math::Vector2 &halfSize)
	{
		//VBO data
		Vertex2DPosUV vertexData[4] =
		{
			Vertex2DPosUV(Vector2(-halfSize.x, -halfSize.y), Vector2(0.0f, 1.0f)),
			Vertex2DPosUV(Vector2(halfSize.x, -halfSize.y), Vector2(1.0f, 1.0f)),
			Vertex2DPosUV(Vector2(halfSize.x, halfSize.y), Vector2(1.0f, 0.0f)),
			Vertex2DPosUV(Vector2(-halfSize.x, halfSize.y), Vector2(0.0f, 0.0f)),
		};

		//IBO data
		GLuint indexData[] = { 0, 1, 2, 3 };

		MeshAttribute attributes[] =
		{
			MeshAttribute::APosition2D,
			MeshAttribute::ACoord,
		};

		Mesh *pMesh = new Mesh(4, (float*)vertexData, 4, indexData, sizeof(Vertex2DPosUV), 2, attributes);
		pMesh->BuildMesh();

		// Return mesh
		return pMesh;
	}

private:
	MeshHelper();
	~MeshHelper();
};
