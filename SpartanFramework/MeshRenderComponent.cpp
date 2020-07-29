#include "stdafx.h"
#include "MeshRenderComponent.h"
#include "Mesh.h"
#include "MaterialManager.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameScene.h"
#include "CameraComponent.h"
#include "Material.h"

namespace Spartan
{
	MeshRenderComponent::MeshRenderComponent() : m_pMeshToRender(nullptr), m_MaterialID(0), BaseComponent("Mesh Renderer")
	{
	}

	MeshRenderComponent::~MeshRenderComponent()
	{
	}

	void MeshRenderComponent::SetMesh(Mesh* pMesh)
	{
		m_pMeshToRender = pMesh;
	}

	void MeshRenderComponent::SetMaterial(size_t materialID)
	{
		m_MaterialID = materialID;
		Material* pMaterial = MaterialManager::GetMaterial(m_MaterialID);
		if (pMaterial == nullptr)
		{
			Utilities::Debug::LogWarning("Material with ID " + to_string(m_MaterialID) + " does not exist!");
			return;
		}
	}

	size_t MeshRenderComponent::GetMaterial()
	{
		return m_MaterialID;
	}

	void MeshRenderComponent::Initialize(const GameContext&)
	{
	}

	void MeshRenderComponent::Update(const GameContext&)
	{
	}

	void MeshRenderComponent::Draw(const GameContext&)
	{
		if (m_pMeshToRender == nullptr)
			return;

		// Set material
		Material* pMaterial = MaterialManager::GetMaterial(m_MaterialID);
		if (pMaterial == nullptr)
		{
			Utilities::Debug::LogWarning("Material with ID " + to_string(m_MaterialID) + " does not exist!");
			return;
		}
		pMaterial->Use();

		auto camInverse = GetGameObject()->GetGameScene()->GetActiveCamera()->GetCameraMatrixInverse();
		auto projection = GetGameObject()->GetGameScene()->GetActiveCamera()->GetProjectionMatrix();
		auto world = GetGameObject()->GetTransform()->GetWorldMatrix();
		auto viewProjection = GetGameObject()->GetGameScene()->GetActiveCamera()->GetViewProjectionMatrix();

		Matrix4X4 worldCamProjection = world * viewProjection;//camInverse * projection;

		/*if (!GetGameObject()->GetTransform()->UseCamera())
			worldCamProjection = camInverse * projectionInverse * world;
		else
			worldCamProjection = camInverse * world;*/

		pMaterial->SetMatrix4("WorldViewProjection", &worldCamProjection.m[0][0]);
		pMaterial->SetShaderVars(this);

		m_pMeshToRender->Draw();

		Material::Reset();
	}
}