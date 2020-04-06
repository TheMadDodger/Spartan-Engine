#include "stdafx.h"
#include "RenderTestScene.h"
#include <GameObject.h>
#include <Components.h>
#include <Mesh.h>
#include <MaterialManager.h>
#include <InputManager.h>
#include <ContentManager.h>
#include "PlanetMaterial.h"

RenderTestScene::RenderTestScene() : GameScene("Render Test Scene")
{
}

RenderTestScene::~RenderTestScene()
{
}

void RenderTestScene::Initialize(const GameContext& gameContext)
{
	size_t id = MaterialManager::CreateMaterial<PlanetMaterial>("./Resources/Shaders/tesselation.fx");

	m_pObject = Instantiate<GameObject>();
	MeshRenderComponent *pMeshRenderer = m_pObject->CreateRuntimeComponent<MeshRenderComponent>();
	//pMeshRenderer->SetMesh(MeshHelper::Generate3DBoxMeshPosColor(Vector3(1.0f, 1.0f, 1.0f), Color::Red(), Color::Blue(), Color::Green(), Color::Gold(), Color::Cyan(), Color::Magenta()));
	//pMeshRenderer->SetMesh(MeshHelper::Generate3DBoxMeshPosColor(Vector2(1.0f, 1.0f), Color::Red()));
	Model* pModel = ContentManager::GetInstance()->Load<Model>("./Resources/Models/planet.fbx");
	pModel->GetMesh(0)->SetPrimitiveTopology(GL_PATCHES);
	pMeshRenderer->SetMesh(pModel->GetMesh(0));
	pMeshRenderer->SetMaterial(id);

	m_pMaterial = MaterialManager::GetMaterial<PlanetMaterial>(id);

	NoiseLayer layer;
	layer.BaseRoughness = 0.55f;
	layer.Roughness = 2.34f;
	layer.MinValue = 1.06f;
	layer.NumLayers = 4;
	layer.Persistance = 0.54f;
	layer.Strength = 0.12f;
	layer.Center = Vector3::Zero();
	layer.UseFirstLayerAsMask = 0;
	layer.NoiseFilterType = NoiseFilterType::Simple;
	m_pMaterial->SetLayer(0, layer);
	layer.BaseRoughness = 1.08f;
	layer.Roughness = 2.34f;
	layer.MinValue = 1.25f;
	layer.NumLayers = 5;
	layer.Persistance = 0.5f;
	layer.Strength = 5.67f;
	layer.UseFirstLayerAsMask = 1;
	layer.NoiseFilterType = NoiseFilterType::Simple;
	m_pMaterial->SetLayer(1, layer);
	layer.BaseRoughness = 1.08f;
	layer.Roughness = 2.34f;
	layer.MinValue = 1.25f;
	layer.NumLayers = 5;
	layer.Persistance = 0.5f;
	layer.Strength = 5.67f;
	layer.UseFirstLayerAsMask = 1;
	layer.NoiseFilterType = NoiseFilterType::Rigid;
	m_pMaterial->SetLayer(2, layer);
	m_pMaterial->SetLayerCount(3);
	//m_pMaterial->EnableWireframe(true);
	//m_pMaterial->SetDoubleSided(true);

	m_pObject->GetTransform()->Translate(0.0f, 0.0f, 0.0f);
	//m_pObject->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0.1f));

	/*auto forward = Vector3(0.01f, 0.01f, 1.0f).Normalized();
	auto up = Math::Cross(Vector3::Up(), forward);
	auto right = Math::Cross(forward, up);
	auto rotMat = Matrix4X4::CreateRotationMatrix(forward, up, right);
	m_pObject->GetTransform()->Rotation = Quaternion(rotMat);
	m_pObject->GetTransform()->Translate(1.0f, 3.0f, 0.0f);*/

	GetActiveCamera()->SetPerspective(45.0f / 180.0f * M_PI, 0.1f, 1000.0f);
	GetActiveCamera()->GetGameObject()->GetTransform()->Translate(0.0f, 0.0f, 2.5f);
	//GetActiveCamera()->Zoom(0.001f);

	gameContext.pInput->AddInputAction(InputAction("Up", InputType::Down, 0, 0, SDL_SCANCODE_UP));
	gameContext.pInput->AddInputAction(InputAction("Down", InputType::Down, 0, 0, SDL_SCANCODE_DOWN));
	gameContext.pInput->AddInputAction(InputAction("Left", InputType::Down, 'q'));
	gameContext.pInput->AddInputAction(InputAction("Right", InputType::Down, 'e'));
	gameContext.pInput->AddInputAction(InputAction("Randomize", InputType::Pressed, 'r'));

	SetEnabled(true);
}

void RenderTestScene::Update(const GameContext& gameContext)
{
	//return;
	//m_pObject->GetTransform()->Translate(100.0f * sin(gameContext.pTime->GetTime()), 100.0f * sin(gameContext.pTime->GetTime()), 100.0f * sin(gameContext.pTime->GetTime()));

	if (gameContext.pInput->IsActionTriggered("Right"))
	{
		m_CameraYaw += 45.0f * gameContext.pTime->GetDeltaTime() / 1000.0f;
	}
	if (gameContext.pInput->IsActionTriggered("Left"))
	{
		m_CameraYaw -= 45.0f * gameContext.pTime->GetDeltaTime() / 1000.0f;
	}
	if (gameContext.pInput->IsActionTriggered("Randomize"))
	{
		//Randomize(time(NULL));
		m_pMaterial->Randomize(Math::Random<int>());
	}


	Matrix4X4 rotation = Matrix4X4::CreateRotationMatrix(Vector3(m_ObjectRot + 90.0f, m_ObjectRot, m_ObjectRot));
	m_pObject->GetTransform()->Rotation = Quaternion(rotation);

	m_ObjectRot += 45.0f * gameContext.pTime->GetDeltaTime() / 1000.0f;

	auto camTransform = GetActiveCamera()->GetGameObject()->GetTransform();

	rotation = Matrix4X4::CreateRotationMatrix(Vector3(m_CameraPitch, m_CameraYaw, 0.0f));
	camTransform->Rotation = Quaternion(rotation);

	Vector2 mouseWheel = gameContext.pInput->GetMouseWheelMovement();
	auto pos = camTransform->Position;
	m_DesiredZ += mouseWheel.y;
	pos.z = Math::Lerp(pos.z, m_DesiredZ, 0.1f);
	GetActiveCamera()->GetGameObject()->GetTransform()->Translate(pos);
}

void RenderTestScene::Draw(const GameContext& gameContext)
{

}
