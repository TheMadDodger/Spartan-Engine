#include "stdafx.h"
#include "Skeleton.h"
#include "Bone.h"

namespace SpartanEngine
{
	Skeleton::Skeleton(bool usesPhysics) : m_UsesPhysics(usesPhysics)//, GameObject("Skeleton")
	{
	}

	Skeleton::~Skeleton()
	{
	}

	Bone* Skeleton::AddBone(Bone* bone)
	{
		if (bone->m_pOwner) return nullptr;
		m_Bones.push_back(bone);
		bone->m_pOwner = this;

		//AddChild(bone);

		return bone;
	}

	void Skeleton::Initialize()
	{
		for (auto pBone : m_Bones)
		{
			pBone->InitializeBone(m_UsesPhysics);
		}
	}

	Bone* Skeleton::GetBone(unsigned int index) const
	{
		if (index <= m_Bones.size())
			return m_Bones[index];

		return nullptr;
	}
}