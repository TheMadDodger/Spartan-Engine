#include "stdafx.h"
#include "BufferTest.h"
#include <MeshRenderComponent.h>
#include "BufferTestMaterial.h"
#include <MaterialManager.h>
#include "TransformComponent.h"
#include "CameraComponent.h"
#include <Mesh.h>

BufferTest::BufferTest() : SpartanEngine::GameScene("Buffer Test")
{
}

BufferTest::~BufferTest()
{
}

void BufferTest::Initialize(const SpartanEngine::GameContext& gameContext)
{
	SpartanEngine::GameObject* pObject = Instantiate<SpartanEngine::GameObject>();
	SpartanEngine::MeshRenderComponent *pMeshRenderer = pObject->CreateRuntimeComponent<SpartanEngine::MeshRenderComponent>();

	SpartanEngine::Model* pModel = SpartanEngine::ContentManager::GetInstance()->Load<SpartanEngine::Model>("./Resources/Models/Sphere.fbx");
	pModel->GetMesh(0)->SetPrimitiveTopology(GL_PATCHES);
	pMeshRenderer->SetMesh(pModel->GetMesh(0));

	size_t matID = SpartanEngine::MaterialManager::CreateMaterial<BufferTestMaterial>("./Resources/Shaders/test.fx");
	pMeshRenderer->SetMaterial(matID);

	pObject->GetTransform()->Translate(0.0f, 0.0f, -40.0f);
	pObject->GetTransform()->SetScale(SpartanEngine::Vector3(10.0f, 10.0f, 10.0f));

	GetActiveCamera()->SetPerspective(60.0f / 180.0f * M_PI, 0.1f, 9999999.0f);

	SetEnabled(true);
}

void BufferTest::Update(const SpartanEngine::GameContext& gameContext)
{
}

void BufferTest::Draw(const SpartanEngine::GameContext& gameContext)
{
}
