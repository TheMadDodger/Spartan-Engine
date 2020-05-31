#include "stdafx.h"
#include "BufferTest.h"
#include <MeshRenderComponent.h>
#include "BufferTestMaterial.h"
#include <MaterialManager.h>
#include "TransformComponent.h"
#include "CameraComponent.h"
#include <Mesh.h>

#include <PhysicsObjectComponent.h>
#include <3DColliders.h>

BufferTest::BufferTest() : SpartanEngine::GameScene("Buffer Test")
{
}

BufferTest::~BufferTest()
{
}

void BufferTest::Initialize(const SpartanEngine::GameContext& gameContext)
{
	/*SpartanEngine::GameObject* pObject = Instantiate<SpartanEngine::GameObject>();
	SpartanEngine::MeshRenderComponent *pMeshRenderer = pObject->CreateRuntimeComponent<SpartanEngine::MeshRenderComponent>();

	SpartanEngine::Model* pModel = SpartanEngine::ContentManager::GetInstance()->Load<SpartanEngine::Model>("./Resources/Models/Sphere.fbx");
	pModel->GetMesh(0)->SetPrimitiveTopology(GL_PATCHES);
	pMeshRenderer->SetMesh(pModel->GetMesh(0));

	size_t matID = SpartanEngine::MaterialManager::CreateMaterial<BufferTestMaterial>("./Resources/Shaders/test.fx");
	pMeshRenderer->SetMaterial(matID);

	pObject->GetTransform()->Translate(0.0f, 0.0f, -40.0f);
	pObject->GetTransform()->SetScale(SpartanEngine::Vector3(10.0f, 10.0f, 10.0f));*/

	GetActiveCamera()->SetPerspective(60.0f / 180.0f * M_PI, 0.1f, 9999999.0f);

	GetActiveCamera()->GetGameObject()->GetTransform()->Translate(0.0f, 0.0f, 10.0f);

	size_t matID = SpartanEngine::MaterialManager::CreateMaterial<SpartanEngine::Material>("./Resources/Shaders/triangle.fx");
	m_Mat2 = SpartanEngine::MaterialManager::CreateMaterial<SpartanEngine::Material>("./Resources/Shaders/triangle2.fx");

	SpartanEngine::GameObject* pGround = Instantiate<SpartanEngine::GameObject>();
	SpartanEngine::PhysicsObjectComponent *pPhysicsObject = pGround->CreateRuntimeComponent<SpartanEngine::PhysicsObjectComponent>();
	pPhysicsObject->SetCollider(new SpartanEngine::Box(SpartanEngine::Vector3(1.0f, 1.0f, 1.0f)));
	pPhysicsObject->SetMass(0.0f);
	SpartanEngine::MeshRenderComponent* pMeshRenderer = pGround->CreateRuntimeComponent<SpartanEngine::MeshRenderComponent>();
	pMeshRenderer->SetMaterial(matID);

	pGround->GetTransform()->Translate(0.0f, -4.0f, 0.0f);

	SpartanEngine::Model* pModel = SpartanEngine::ContentManager::GetInstance()->Load<SpartanEngine::Model>("./Resources/Models/Cube.fbx");
	pMeshRenderer->SetMesh(pModel->GetMesh(0));

	SpartanEngine::GameObject* pSphere = Instantiate<SpartanEngine::GameObject>();
	pPhysicsObject = pSphere->CreateRuntimeComponent<SpartanEngine::PhysicsObjectComponent>();
	pPhysicsObject->SetCollider(new SpartanEngine::Sphere(1.0f));
	pMeshRenderer = pSphere->CreateRuntimeComponent<SpartanEngine::MeshRenderComponent>();
	pMeshRenderer->SetMaterial(m_Mat2);

	pSphere->GetTransform()->SetScale(SpartanEngine::Vector3(2.0f, 2.0f, 2.0f));

	pModel = SpartanEngine::ContentManager::GetInstance()->Load<SpartanEngine::Model>("./Resources/Models/Sphere.fbx");
	pMeshRenderer->SetMesh(pModel->GetMesh(0));

	SetEnabled(true);
}

void BufferTest::Update(const SpartanEngine::GameContext& gameContext)
{
}

void BufferTest::Draw(const SpartanEngine::GameContext& gameContext)
{
}
