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
#include <Model.h>

BufferTest::BufferTest() : Spartan::GameScene("Buffer Test")
{
}

BufferTest::~BufferTest()
{
}

void BufferTest::Initialize(const Spartan::GameContext& gameContext)
{
	/*Spartan::GameObject* pObject = Instantiate<Spartan::GameObject>();
	Spartan::MeshRenderComponent *pMeshRenderer = pObject->CreateRuntimeComponent<Spartan::MeshRenderComponent>();

	Spartan::Model* pModel = Spartan::ContentManager::GetInstance()->Load<Spartan::Model>("./Resources/Models/Sphere.fbx");
	pModel->GetMesh(0)->SetPrimitiveTopology(GL_PATCHES);
	pMeshRenderer->SetMesh(pModel->GetMesh(0));

	size_t matID = Spartan::MaterialManager::CreateMaterial<BufferTestMaterial>("./Resources/Shaders/test.fx");
	pMeshRenderer->SetMaterial(matID);

	pObject->GetTransform()->Translate(0.0f, 0.0f, -40.0f);
	pObject->GetTransform()->SetScale(Spartan::Vector3(10.0f, 10.0f, 10.0f));*/

	GetActiveCamera()->SetPerspective(60.0f / 180.0f * M_PI, 0.1f, 9999999.0f);

	GetActiveCamera()->GetGameObject()->GetTransform()->Translate(0.0f, 0.0f, 10.0f);

	size_t matID = Spartan::MaterialManager::CreateMaterial<Spartan::Material>("./Resources/Shaders/triangle.fx");
	m_Mat2 = Spartan::MaterialManager::CreateMaterial<Spartan::Material>("./Resources/Shaders/triangle2.fx");

	Spartan::GameObject* pGround = Instantiate<Spartan::GameObject>();
	pGround->SetName("Cube");
	Spartan::PhysicsObjectComponent *pPhysicsObject = pGround->CreateRuntimeComponent<Spartan::PhysicsObjectComponent>();
	pPhysicsObject->SetCollider(new Spartan::Box(Spartan::Vector3(1.0f, 1.0f, 1.0f)));
	pPhysicsObject->SetMass(0.0f);
	Spartan::MeshRenderComponent* pMeshRenderer = pGround->CreateRuntimeComponent<Spartan::MeshRenderComponent>();
	pMeshRenderer->SetMaterial(matID);

	pGround->GetTransform()->Translate(0.0f, -4.0f, 0.0f);

	Spartan::Model* pModel = Spartan::ContentManager::GetInstance()->Load<Spartan::Model>("./Resources/Models/Cube.fbx");
	pMeshRenderer->SetMesh(pModel->GetMesh(0));

	Spartan::GameObject* pSphere = Instantiate<Spartan::GameObject>();
	pSphere->SetName("Sphere");
	pPhysicsObject = pSphere->CreateRuntimeComponent<Spartan::PhysicsObjectComponent>();
	pPhysicsObject->SetCollider(new Spartan::Sphere(1.0f));
	pMeshRenderer = pSphere->CreateRuntimeComponent<Spartan::MeshRenderComponent>();
	pMeshRenderer->SetMaterial(m_Mat2);

	pSphere->GetTransform()->SetScale(Spartan::Vector3(2.0f, 2.0f, 2.0f));

	pModel = Spartan::ContentManager::GetInstance()->Load<Spartan::Model>("./Resources/Models/Sphere.fbx");
	pMeshRenderer->SetMesh(pModel->GetMesh(0));

	SetEnabled(true);
}

void BufferTest::Update(const Spartan::GameContext& gameContext)
{
}

void BufferTest::Draw(const Spartan::GameContext& gameContext)
{
}
