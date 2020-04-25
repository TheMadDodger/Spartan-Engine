#pragma once
#include "BaseComponent.h"

namespace SpartanEngine
{
	enum ShakeMode
	{
		Normal,
		IncreaseOverTime,
		DecreaseOverTime,
	};

	class ShakeComponent : public BaseComponent
	{
	public:
		ShakeComponent();
		virtual ~ShakeComponent();

		void Shake(const Vector2& amplitude, float time);
		void SetShakeMode(const ShakeMode& mode);

	private:
		virtual BaseComponent* Create() override { return new ShakeComponent(); }

	private:
		virtual void Update(const GameContext& gameContext) override;

	private:
		float m_ShakeTimer = 0.0f;
		float m_ShakeStartTime = 0.0f;
		Vector2 m_ShakeAmplitudes;

		Vector2 m_OriginalPosition;

		ShakeMode m_ShakeMode = ShakeMode::Normal;
	};
}