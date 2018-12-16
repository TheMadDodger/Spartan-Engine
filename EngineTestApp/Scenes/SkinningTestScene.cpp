#include "stdafx.h"
#include "SkinningTestScene.h"
#include "Bone.h"
#include "Skeleton.h"
#include "Components.h"

SkinningTestScene::SkinningTestScene() : GameScene("Skinning Test Scene")
{
}

SkinningTestScene::~SkinningTestScene()
{
	delete m_pSkeleton;
}

void SkinningTestScene::Initialize(const GameContext &)
{
	m_pSkeleton = new Skeleton();
	m_pRootBone = m_pSkeleton->AddBone(new Bone(100.f, 0.f));
	m_pChildBone = m_pRootBone->AddChildBone(new Bone(100.f, 0.f));
	m_pSkeleton->Initialize();

	auto pObject = new GameObject();
	pObject->AddComponent(new SkinnedMeshComponent(m_pSkeleton));
	AddChild(pObject);
}

void SkinningTestScene::Update(const GameContext &gameContext)
{
	m_pRootBone->GetTransform()->Rotate(Vector3(0.f, 0.f, sin(gameContext.pTime->GetTime())));
	m_pChildBone->GetTransform()->Rotate(Vector3(0.f, 0.f, -cos(gameContext.pTime->GetTime())));
}

void SkinningTestScene::Draw(const GameContext &)
{
}
