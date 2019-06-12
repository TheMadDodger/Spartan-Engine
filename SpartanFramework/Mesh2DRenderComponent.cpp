#include "stdafx.h"
#include "Mesh2DRenderComponent.h"
#include "Mesh.h"
#include "MaterialManager.h"

Mesh2DRenderComponent::Mesh2DRenderComponent() : m_pMesh(nullptr), m_MaterialID(0)
{
}

Mesh2DRenderComponent::Mesh2DRenderComponent(Mesh2D *pMesh) : m_pMesh(pMesh), m_MaterialID(0)
{
}

Mesh2DRenderComponent::~Mesh2DRenderComponent()
{
	if(m_pMesh)
		delete m_pMesh;

	m_pMesh = nullptr;
}

void Mesh2DRenderComponent::SetMesh(Mesh2D *pMesh)
{
	if(m_pMesh)
		delete m_pMesh;

	m_pMesh = pMesh;
}

void Mesh2DRenderComponent::SetMaterial(size_t materialID)
{
	m_MaterialID = materialID;
}

void Mesh2DRenderComponent::Initialize(const GameContext &)
{
}

void Mesh2DRenderComponent::Update(const GameContext &)
{
}

void Mesh2DRenderComponent::Draw(const GameContext &)
{
	if (m_pMesh == nullptr) return;

	// Set material
	Material *pMaterial = MaterialManager::GetMaterial(m_MaterialID);
	if (pMaterial == nullptr)
	{
		Utilities::Debug::LogWarning("Material with ID " + to_string(m_MaterialID) + " does not exist!");
		return;
	}
	pMaterial->Use();

	// Bind the vertex array
	glBindVertexArray(m_pMesh->GetVertexArrayID());

	// Draw the vertices using the index buffer
	glDrawElements(GL_TRIANGLES, m_pMesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);//(GLvoid*)(m_pMesh->GetVertexSize() * m_pMesh->GetVertexCount()));

	// Unbind vertex array
	glBindVertexArray(0);

	// Reset material
	Material::Reset();
}
