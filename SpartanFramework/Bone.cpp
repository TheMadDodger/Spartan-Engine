#include "stdafx.h"
#include "Bone.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Skeleton.h"

Bone::Bone(float length, float rotation) :
	m_Length(length), m_Rotation(rotation), GameObject("Bone")
{
}

Bone::~Bone()
{
	if (!GetGameScene())
	{
		for (auto pChild : m_ChildBones)
		{
			delete pChild;
		}
		m_ChildBones.clear();
	}
}

Bone *Bone::AddChildBone(Bone *bone)
{
	if (!bone) return nullptr;

	bone->m_pParentBone = this;
	m_pOwner->AddBone(bone);

	return bone;
}

const Matrix3X3 & Bone::GetBindPose() const
{
	return m_BindingPose;
}

void Bone::Initialize(const GameContext &)
{
}

void Bone::Update(const GameContext &)
{
}

void Bone::Draw(const GameContext &gameContext)
{
	glPushMatrix();
	GetTransform()->ApplyTransform();
	gameContext.pRenderer->DrawLine(Vector2::Zero(), Vector2(m_Length, 0.f), Color::White());
	glPopMatrix();
}

void Bone::InitializeBone(bool usePhysics)
{
	if (GetParent())
		GetParent()->RemoveChild(this);

	if (GetGameScene())
		GetGameScene()->RemoveChild(this);

	// Initialize transform
	GetTransform()->Rotate(Vector3(0.f, 0.f, m_Rotation));

	if (m_pParentBone)
		GetTransform()->Translate(Math::LengthDir(m_pParentBone->m_Length, m_pParentBone->GetTransform()->Rotation.z));

	if (usePhysics)
	{
		SceneManager::GetInstance()->GetCurrentScene()->AddChild(this);

		// Do physics stuff
	}
	else
	{
		// Check if has bone parent
		if (m_pParentBone)
		{
			// Attach to this bone as child
			m_pParentBone->AddChild(this);
		}
		else
		{
			// Attach to scene
			SceneManager::GetInstance()->GetCurrentScene()->AddChild(this);
		}
	}

	GetTransform()->BuildTransform();

	CalculateBindPose();
}

void Bone::CalculateBindPose()
{
	m_BindingPose = GetTransform()->GetWorldMatrix().Inverse();
}
