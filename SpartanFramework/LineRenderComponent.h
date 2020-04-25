#pragma once
#include "BaseComponent.h"

namespace SpartanEngine
{
	class LineRenderComponent : public BaseComponent
	{
	public:
		LineRenderComponent();
		virtual ~LineRenderComponent();

		void SetColor(Color color);

		void SetStartAndEnd(Vector2 startPos, Vector2 endPos);

		Vector2 m_StartPos;
		Vector2 m_EndPos;
		Color m_Color;

	private:
		void Draw(const GameContext& gameContext) override;
		COMPONENT_EDITOR(LineRenderComponent)
	};
}