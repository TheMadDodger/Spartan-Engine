#pragma once
#include "BaseComponent.h"

namespace Spartan
{
	class RigidBody2DComponent : public BaseComponent
	{
	public:
		RigidBody2DComponent();
		virtual ~RigidBody2DComponent();

		b2Body* Getb2Body() { return m_Body; };

		Vector2 m_BodyPivot;
		b2BodyType m_BodyType;

	protected:
		void Initialize(const GameContext& gameContext) override;
		void OnDestroy() override;
		//void Update(const GameContext &gameContext) override;
		//void Draw(const GameContext &gameContext) override;

	private:
		COMPONENT_EDITOR(RigidBody2DComponent)
		
		b2Body* m_Body = nullptr;
	};
}