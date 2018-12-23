#include "stdafx.h"
#include "SkinnedMeshComponent.h"
#include "SkinnedQuad.h"
#include "GameObject.h"
#include "Components.h"

SkinnedMeshComponent::SkinnedMeshComponent(Skeleton *pSkeleton) : m_pSkeleton(pSkeleton)
{
}

SkinnedMeshComponent::~SkinnedMeshComponent()
{
	for (auto pQuad : m_Quads)
	{
		delete pQuad;
	}
	m_Quads.clear();
}

void SkinnedMeshComponent::Initialize(const GameContext &)
{
	vector<BlendWeightData> blendData1;
	vector<BlendWeightData> blendData2;

	BlendWeightData blend1;
	blend1.BoneIndeces.push_back(0);
	blend1.BoneWeights.push_back(1.f);

	BlendWeightData blend2;
	blend2.BoneIndeces.push_back(0);
	blend2.BoneIndeces.push_back(1);
	blend2.BoneWeights.push_back(0.5f);
	blend2.BoneWeights.push_back(0.5f);

	BlendWeightData blend3;
	blend3.BoneIndeces.push_back(1);
	blend3.BoneWeights.push_back(1.f);
	
	blendData1.push_back(blend1);
	blendData1.push_back(blend1);
	blendData1.push_back(blend2);
	blendData1.push_back(blend2);

	blendData2.push_back(blend2);
	blendData2.push_back(blend2);
	blendData2.push_back(blend3);
	blendData2.push_back(blend3);

	m_Quads.push_back(new SkinnedQuad(Vector2(0.0f, 0.0f), Vector2(100.0f, 100.0f), blendData1, nullptr, m_pSkeleton));
	m_Quads.push_back(new SkinnedQuad(Vector2(100.0f, 0.0f), Vector2(200.0f, 100.0f), blendData2, nullptr, m_pSkeleton));
}

void SkinnedMeshComponent::Update(const GameContext &)
{
	for (auto pQuad : m_Quads)
	{
		pQuad->Update();
	}
}

void SkinnedMeshComponent::Draw(const GameContext &gameContext)
{
	glPushMatrix();
	GetGameObject()->GetTransform()->ApplyTransform();
	for (auto pQuad : m_Quads)
	{
		pQuad->Draw(gameContext);
	}
	glPopMatrix();
}

BaseComponent *SkinnedMeshComponent::Create()
{
	return new SkinnedMeshComponent(nullptr);
}
