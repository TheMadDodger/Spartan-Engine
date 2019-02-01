#pragma once
#include <GameObject.h>

class Skeleton;

class SkeletonObject : public GameObject
{
public:
	SkeletonObject(Skeleton *pSkeleton);
	virtual ~SkeletonObject();

	Skeleton *GetSkeleton() { return m_pSkeleton; }

	void Initialize(const GameContext &) override;

private:
	Skeleton *m_pSkeleton;
};

