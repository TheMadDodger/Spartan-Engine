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
	/*if(m_pMesh)
		delete m_pMesh;

	m_pMesh = nullptr;*/
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
	auto projectionInverse = GetGameObject()->GetGameScene()->GetActiveCamera()->GetProjectionMatrixInverse();
	auto world = GetGameObject()->GetTransform()->GetWorldMatrix();

	Matrix3X3 worldCamProjection;
	if (GetGameObject()->GetTransform()->UseCamera())
		worldCamProjection = world * projectionInverse;
	else
		worldCamProjection = camInverse * world;

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
}
