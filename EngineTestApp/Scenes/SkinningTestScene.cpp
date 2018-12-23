#include "stdafx.h"
#include "SkinningTestScene.h"
#include "Bone.h"
#include "Skeleton.h"
#include "Components.h"
#include "InputManager.h"

SkinningTestScene::SkinningTestScene() : GameScene("Skinning Test Scene")
{
}

SkinningTestScene::~SkinningTestScene()
{
	delete m_pSkeleton;
}

void SkinningTestScene::Initialize(const GameContext &gameContext)
{
	m_pSkeleton = new Skeleton();
	m_pRootBone = m_pSkeleton->AddBone(new Bone(100.f, 0.f));
	m_pChildBone = m_pRootBone->AddChildBone(new Bone(100.f, 0.f));
	m_pSkeleton->Initialize();

	auto pObject = new GameObject();
	pObject->AddComponent(new SkinnedMeshComponent(m_pSkeleton));
	AddChild(pObject);

	gameContext.pInput->AddInputAction(InputAction("Forward", Down, 'w', 0, SDL_SCANCODE_LEFT));
	gameContext.pInput->AddInputAction(InputAction("Backward", Down, 's'));
	gameContext.pInput->AddInputAction(InputAction("Left", Down, 'a'));
	gameContext.pInput->AddInputAction(InputAction("Right", Down, 'd'));

	gameContext.pInput->AddInputAction(InputAction("ZoomOut", Pressed, 'o'));
	gameContext.pInput->AddInputAction(InputAction("ZoomIn", Pressed, 'i'));

	gameContext.pInput->AddInputAction(InputAction("Shoot", Pressed, 'f'));

	gameContext.pInput->AddInputAction(InputAction("ChangeScene", Pressed, 'p'));

	gameContext.pInput->AddInputAction(InputAction("AddPoint", Pressed, -1, SDL_BUTTON_LEFT));
	gameContext.pInput->AddInputAction(InputAction("RemovePoint", Pressed, -1, SDL_BUTTON_RIGHT));
}

void SkinningTestScene::Update(const GameContext &gameContext)
{
	m_pRootBone->GetTransform()->Rotate(Vector3(0.f, 0.f, sin(gameContext.pTime->GetTime())));
	m_pChildBone->GetTransform()->Rotate(Vector3(0.f, 0.f, -cos(gameContext.pTime->GetTime())));

	if (gameContext.pInput->IsActionTriggered("Forward"))
	{
		GetActiveCamera()->GetGameObject()->GetTransform()->Translate(GetActiveCamera()->GetGameObject()->GetTransform()->Position + Vector2(0.0f, 1.0f) * gameContext.pTime->GetDeltaTime());
		//m_pPartObject->GetTransform()->Translate(Vector2(0.0f, 1.0f) * gameContext.pTime->GetDeltaTime());
	}
	if (gameContext.pInput->IsActionTriggered("Backward"))
	{
		GetActiveCamera()->GetGameObject()->GetTransform()->Translate(GetActiveCamera()->GetGameObject()->GetTransform()->Position + Vector2(0.0f, -1.0f) * gameContext.pTime->GetDeltaTime());
		//m_pPartObject->GetTransform()->Translate(Vector2(0.0f, -1.0f) * gameContext.pTime->GetDeltaTime());
	}
	if (gameContext.pInput->IsActionTriggered("Left"))
	{
		GetActiveCamera()->GetGameObject()->GetTransform()->Translate(GetActiveCamera()->GetGameObject()->GetTransform()->Position + Vector2(-1.0f, 0.0f) * gameContext.pTime->GetDeltaTime());
		//m_pPartObject->GetTransform()->Translate(Vector2(-1.0f, 0.0f) * gameContext.pTime->GetDeltaTime());
	}
	if (gameContext.pInput->IsActionTriggered("Right"))
	{
		GetActiveCamera()->GetGameObject()->GetTransform()->Translate(GetActiveCamera()->GetGameObject()->GetTransform()->Position + Vector2(1.0f, 0.0f) * gameContext.pTime->GetDeltaTime());
		//m_pPartObject->GetTransform()->Translate(Vector2(1.0f, 0.0f) * gameContext.pTime->GetDeltaTime());
	}
}

void SkinningTestScene::Draw(const GameContext &)
{
}
