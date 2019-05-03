#pragma once
#include "BaseComponent.h"
#include "Colliders.h"
#include "PhysicsMaterial.h"

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent(Collider *collider, const PhysicsMaterial &physicsMat = PhysicsMaterial());
	virtual ~ColliderComponent();

	virtual BaseComponent *Create() { return new ColliderComponent(nullptr); }

	void UpdateCollider(Collider *newCollider);


protected:
	void Initialize(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	friend class RigidBodyComponent;

	Collider *m_pCollider = nullptr;
	b2FixtureDef m_FixtureDef;
	b2Fixture *m_pFixture = nullptr;
	PhysicsMaterial m_PhysicsMaterial;
};

