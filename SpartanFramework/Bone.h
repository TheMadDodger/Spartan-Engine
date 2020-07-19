#pragma once
#include "GameObject.h"

namespace Spartan
{
	class Skeleton;

	class Bone : public GameObject
	{
	public:
		Bone(float length, float rotation);
		virtual ~Bone();

		Bone* AddChildBone(Bone* bone);

		const Matrix4X4& GetBindPose() const;

	private:
		virtual void Initialize(const GameContext& gameContext);
		virtual void Update(const GameContext& gameContext);
		virtual void Draw(const GameContext& gameContext);

	private:
		friend class Skeleton;
		void InitializeBone(bool usePhysics);
		void CalculateBindPose();

	private:
		Skeleton* m_pOwner;
		Bone* m_pParentBone;
		std::vector<Bone*> m_ChildBones;

		Matrix4X4 m_BindingPose;
		float m_Length;
		float m_Rotation;
	};
}