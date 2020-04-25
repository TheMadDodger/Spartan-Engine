#pragma once
#include "BaseComponent.h"

namespace SpartanEngine
{
	class RigidBodyComponent : public BaseComponent
	{
	public:
		RigidBodyComponent();
		virtual ~RigidBodyComponent();

		b2Body* Getb2Body() { return m_Body; };

		Vector2 m_BodyPivot;
		b2BodyType m_BodyType;

	protected:
		void Initialize(const GameContext& gameContext) override;
		void OnDestroy() override;
		//void Update(const GameContext &gameContext) override;
		//void Draw(const GameContext &gameContext) override;

	private:
		COMPONENT_EDITOR(RigidBodyComponent)

			b2Body* m_Body = nullptr;
	};
}