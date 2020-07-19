#pragma once
#include "BaseComponent.h"
#include "2DColliders.h"
#include "PhysicsMaterial.h"

namespace Spartan
{
	class Collider2DComponent : public BaseComponent
	{
	public:
		Collider2DComponent();
		virtual ~Collider2DComponent();

		void SetCollider(Collider2D* newCollider);
		void UpdateCollider(Collider2D* newCollider);

		PhysicsMaterial m_PhysicsMaterial;

	protected:
		void Initialize(const GameContext& gameContext) override;
		void Draw(const GameContext& gameContext) override;

	private:
		COMPONENT_EDITOR(Collider2DComponent)

	private:
		friend class RigidBody2DComponent;

		Collider2D* m_pCollider = nullptr;
		b2FixtureDef m_FixtureDef;
		b2Fixture* m_pFixture = nullptr;
	};
}