#pragma once
#include "GameScene.h"

class Skeleton;
class Bone;

class SkinningTestScene : public GameScene
{
public:
	SkinningTestScene();
	virtual ~SkinningTestScene();

private:
	virtual void Initialize(const GameContext &gameContext);
	virtual void Update(const GameContext &gameContext);
	virtual void Draw(const GameContext &gameContext);

private:
	Skeleton *m_pSkeleton;
	Bone *m_pRootBone;
	Bone *m_pChildBone;
};

