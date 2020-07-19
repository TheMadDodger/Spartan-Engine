#pragma once
#include "SEObject.h"

namespace Spartan
{
	class Bone;

	class Skeleton : SEObject
	{
	public:
		Skeleton(bool usesPhysics = false);
		~Skeleton();

		Bone* AddBone(Bone* bone);
		void Initialize();
		Bone* GetBone(unsigned int index) const;

	private:
		bool m_UsesPhysics;
		std::vector<Bone*> m_Bones;
	};
}