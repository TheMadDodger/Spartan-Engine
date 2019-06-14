#pragma once
#include "stdafx.h"
#include "VertexHelpers.h"

#define MEMBER_OFFSET(s,m) ((char *)NULL + (offsetof(s,m)))
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

enum Mesh2DAttribute : unsigned int
{
	APosition2D = 0,
	AColor = 1,
	ACoord = 2,
};

class Mesh2D
{
public:
	Mesh2D(size_t vertexCount, float *pVertices, size_t indexCount, unsigned int *pIndices, size_t vertexSize, size_t attributeCount, Mesh2DAttribute *attributes) :
		m_VertexCount(vertexCount), m_pVertices(pVertices), m_IndexCount(indexCount), m_pIndices(pIndices), m_VertexSize(vertexSize), m_AttributeCount(attributeCount), m_pAttributes(new Mesh2DAttribute[m_AttributeCount])
	{
		memcpy(m_pAttributes, attributes, m_AttributeCount * sizeof(unsigned int));
	}
	virtual ~Mesh2D()
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

	void Prepare()
	{

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

private:
	friend class Mesh2DRenderComponent;

	void ApplyAttributes()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);

		size_t offset = 0;
		for (size_t i = 0; i < m_AttributeCount; i++)
		{
			glEnableVertexAttribArray(i);
			Utilities::Debug::LogGLError(glGetError());

			Mesh2DAttribute attribute = m_pAttributes[i];

			switch (attribute)
			{
			case AColor:
				glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, m_VertexSize, (void*)offset);
				Utilities::Debug::LogGLError(glGetError());
				offset += 4 * sizeof(GLfloat);
				break;
			case APosition2D:
			case ACoord:
				//glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, m_VertexSize, (void*)offset);
				glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, m_VertexSize, (void*)offset);
				Utilities::Debug::LogGLError(glGetError());
				offset += 2 * sizeof(GLfloat);
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
		glDrawElements(GL_TRIANGLE_FAN, m_IndexCount, GL_UNSIGNED_INT, NULL);
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

	size_t m_VertexSize;
	size_t m_AttributeCount;
	Mesh2DAttribute *m_pAttributes;
};

class MeshHelper
{
public:
	static Mesh2D *Generate2DBoxMeshPosColor(const Math::Vector2 &halfSize, const Color &color)
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

		Mesh2DAttribute attributes[] =
		{
			Mesh2DAttribute::APosition2D,
			Mesh2DAttribute::AColor,
		};

		Mesh2D *pMesh = new Mesh2D(4, (float*)vertexData, 4, indexData, sizeof(Vertex2DPosColor), 2, attributes);
		pMesh->BuildMesh();

		// Return mesh
		return pMesh;
	}

	static Mesh2D *Generate2DBoxMeshPosCoord(const Math::Vector2 &halfSize)
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

		Mesh2DAttribute attributes[] =
		{
			Mesh2DAttribute::APosition2D,
			Mesh2DAttribute::ACoord,
		};

		Mesh2D *pMesh = new Mesh2D(4, (float*)vertexData, 4, indexData, sizeof(Vertex2DPosUV), 2, attributes);
		pMesh->BuildMesh();

		// Return mesh
		return pMesh;
	}

private:
	MeshHelper();
	~MeshHelper();
};
