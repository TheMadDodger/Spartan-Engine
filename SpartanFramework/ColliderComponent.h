#pragma once
#include "BaseComponent.h"
#include "Colliders.h"
#include "PhysicsMaterial.h"

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent();
	virtual ~ColliderComponent();

	void SetCollider(Collider* newCollider);
	void UpdateCollider(Collider *newCollider);

	PhysicsMaterial m_PhysicsMaterial;

protected:
	void Initialize(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	COMPONENT_EDITOR(ColliderComponent)

private:
	friend class RigidBodyComponent;

	Collider *m_pCollider = nullptr;
	b2FixtureDef m_FixtureDef;
	b2Fixture *m_pFixture = nullptr;
};

