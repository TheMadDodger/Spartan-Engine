#pragma once
#include "BaseComponent.h"
#include "Colliders.h"

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent(Collider *collider);
	virtual ~ColliderComponent();

	virtual BaseComponent *Create() { return new ColliderComponent(nullptr); }

protected:
	void Initialize(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	Collider *m_pCollider = nullptr;
	b2FixtureDef m_FixtureDef;
	b2Fixture *m_pFixture = nullptr;
};

