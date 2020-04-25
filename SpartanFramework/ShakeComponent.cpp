#include "stdafx.h"
#include "ShakeComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace SpartanEngine
{
	ShakeComponent::ShakeComponent()
	{
	}

	ShakeComponent::~ShakeComponent()
	{
	}

	void ShakeComponent::Shake(const Vector2& amplitude, float time)
	{
		m_ShakeAmplitudes = amplitude;
		m_ShakeTimer = time;
		m_ShakeStartTime = time;

		m_OriginalPosition = GetGameObject()->GetTransform()->Position;
	}

	void ShakeComponent::SetShakeMode(const ShakeMode& mode)
	{
		m_ShakeMode = mode;
	}

	void ShakeComponent::Update(const GameContext& gameContext)
	{
		if (m_ShakeTimer > 0.0f)
		{
			float factor = 1.0f;

			switch (m_ShakeMode)
			{
			case Normal:
				// Do nothing
				break;
			case IncreaseOverTime:
				factor = 1.0f - m_ShakeTimer / m_ShakeStartTime;
				break;
			case DecreaseOverTime:
				factor = m_ShakeTimer / m_ShakeStartTime;
				break;
			default:
				break;
			}

			Vector2 shake;
			shake.x = RandomRange(-1.0f, 1.0f) * m_ShakeAmplitudes.x * factor;
			shake.y = RandomRange(-1.0f, 1.0f) * m_ShakeAmplitudes.y * factor;

			GetGameObject()->GetTransform()->Translate(m_OriginalPosition + shake);

			m_ShakeTimer -= gameContext.pTime->GetDeltaTime() / 1000.0f;
		}
	}
}