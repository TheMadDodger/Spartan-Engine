#include "stdafx.h"
#include "Mesh2DRenderComponent.h"
#include "Mesh.h"
#include "MaterialManager.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameScene.h"
#include "CameraComponent.h"
#include "Material.h"

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
	Material *pMaterial = MaterialManager::GetMaterial(m_MaterialID);
	if (pMaterial == nullptr)
	{
		Utilities::Debug::LogWarning("Material with ID " + to_string(m_MaterialID) + " does not exist!");
		return;
	}
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

	auto camInverse = GetGameObject()->GetGameScene()->GetActiveCamera()->GetCameraProjectionMatrixInverse();
	auto world = GetGameObject()->GetTransform()->GetWorldMatrix();
	auto worldCamProjection = camInverse * world;

	float pMatrix[9];
	size_t index = 0;
	for (size_t x = 0; x < 3; x++)
	{
		for (size_t y = 0; y < 3; y++)
		{
			pMatrix[index] = worldCamProjection.m[x][y];
			++index;
		}
	}

	pMaterial->SetMatrix("Projection", pMatrix);
	pMaterial->SetShaderVars(this);

	m_pMesh->ApplyAttributes();
	m_pMesh->Draw();
	m_pMesh->DrawEnd();

	Material::Reset();

	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_pMesh->GetVertexBufferID());
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	////Set index data and render
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pMesh->GetIndexBufferID());
	//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	////Disable vertex position
	//glDisableVertexAttribArray(0);

	// Bind the vertex array
	//glBindVertexArray(m_pMesh->GetVertexArrayID());
	//Utilities::Debug::LogGLError(glGetError());

	//m_pMesh->Prepare();

	// Draw the vertices using the index buffer
	//glDrawElements(GL_TRIANGLES, m_pMesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);//(GLvoid*)(m_pMesh->GetVertexSize() * m_pMesh->GetVertexCount()));
	//Utilities::Debug::LogGLError(glGetError());

	// Unbind vertex array
	//glBindVertexArray(0);
	//Utilities::Debug::LogGLError(glGetError());
}
