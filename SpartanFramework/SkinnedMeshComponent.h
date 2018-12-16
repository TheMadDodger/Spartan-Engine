#pragma once
#include "BaseComponent.h"

class Skeleton;
class SkinnedQuad;

class SkinnedMeshComponent : public BaseComponent
{
public:
	SkinnedMeshComponent(Skeleton *pSkeleton);
	virtual ~SkinnedMeshComponent();

private:
	virtual void Initialize(const GameContext &gameContext);
	virtual void Update(const GameContext &gameContext);
	virtual void Draw(const GameContext &gameContext);

	virtual BaseComponent *Create();

private:
	vector<SkinnedQuad*> m_Quads;
	Skeleton *m_pSkeleton;
};

