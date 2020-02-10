#include "stdafx.h"
#include "RenderTestScene.h"
#include <GameObject.h>
#include <Components.h>
#include <Mesh.h>
#include <MaterialManager.h>
#include <InputManager.h>

const GLfloat RenderTestScene::g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

RenderTestScene::RenderTestScene() : GameScene("Render Test Scene")
{
}

RenderTestScene::~RenderTestScene()
{
}

void RenderTestScene::Initialize(const GameContext& gameContext)
{
	size_t id = MaterialManager::CreateMaterial<Material>("./Resources/Shaders/pos_color3D");

	m_pObject = Instantiate<GameObject>();
	MeshRenderComponent *pMeshRenderer = m_pObject->CreateRuntimeComponent<MeshRenderComponent>();
	pMeshRenderer->SetMesh(MeshHelper::Generate3DBoxMeshPosColor(Vector3(1.0f, 1.0f, 1.0f), Color::Red(), Color::Blue(), Color::Green(), Color::Gold(), Color::Cyan(), Color::Magenta()));
	//pMeshRenderer->SetMesh(MeshHelper::Generate3DBoxMeshPosColor(Vector2(1.0f, 1.0f), Color::Red()));
	pMeshRenderer->SetMaterial(id);

	m_pObject->GetTransform()->Translate(0.0f, 0.0f, 0.0f);

	/*auto forward = Vector3(0.01f, 0.01f, 1.0f).Normalized();
	auto up = Math::Cross(Vector3::Up(), forward);
	auto right = Math::Cross(forward, up);
	auto rotMat = Matrix4X4::CreateRotationMatrix(forward, up, right);
	m_pObject->GetTransform()->Rotation = Quaternion(rotMat);
	m_pObject->GetTransform()->Translate(1.0f, 3.0f, 0.0f);*/

	GetActiveCamera()->SetPerspective(45.0f / 180.0f * M_PI, 0.1f, 1000.0f);
	GetActiveCamera()->GetGameObject()->GetTransform()->Translate(0.0f, 0.0f, 2.5f);
	//GetActiveCamera()->Zoom(0.001f);

	gameContext.pInput->AddInputAction(InputAction("Left", InputType::Down, 'q'));
	gameContext.pInput->AddInputAction(InputAction("Right", InputType::Down, 'e'));

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

	Matrix4X4 rotation = Matrix4X4::CreateRotationMatrix(Vector3(m_ObjectRot, m_ObjectRot, m_ObjectRot));
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
