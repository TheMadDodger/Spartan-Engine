#pragma once
#include "BaseComponent.h"

namespace Spartan
{
	class Skeleton;
	class SkinnedQuad;

	class SkinnedMeshComponent : public BaseComponent
	{
	public:
		SkinnedMeshComponent();
		virtual ~SkinnedMeshComponent();

		Skeleton* m_pSkeleton;

	private:
		virtual void Initialize(const GameContext& gameContext);
		virtual void Update(const GameContext& gameContext);
		virtual void Draw(const GameContext& gameContext);

		COMPONENT(SkinnedMeshComponent);

	private:
		vector<SkinnedQuad*> m_Quads;
	};
}