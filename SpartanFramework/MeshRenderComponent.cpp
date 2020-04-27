#include "stdafx.h"
#include "MeshRenderComponent.h"
#include "Mesh.h"
#include "MaterialManager.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameScene.h"
#include "CameraComponent.h"
#include "Material.h"

namespace SpartanEngine
{
	MeshRenderComponent::MeshRenderComponent() : m_pMesh(nullptr), m_MaterialID(0)
	{
	}

	MeshRenderComponent::~MeshRenderComponent()
	{
		/*if(m_pMesh)
			delete m_pMesh;

		m_pMesh = nullptr;*/
	}

	void MeshRenderComponent::SetMesh(Mesh* pMesh)
	{
		if (m_pMesh)
			delete m_pMesh;

		m_pMesh = pMesh;
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
		if (m_pMesh == nullptr) return;

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

		Matrix4X4 worldCamProjection = world * camInverse * projection;

		Vector4 test = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		Vector4 result = worldCamProjection * test;

		/*if (!GetGameObject()->GetTransform()->UseCamera())
			worldCamProjection = camInverse * projectionInverse * world;
		else
			worldCamProjection = camInverse * world;*/

		pMaterial->SetMatrix4("WorldViewProjection", &worldCamProjection.m[0][0]);
		pMaterial->SetShaderVars(this);

		m_pMesh->ApplyAttributes();
		m_pMesh->Draw();
		m_pMesh->DrawEnd();

		Material::Reset();
	}
}