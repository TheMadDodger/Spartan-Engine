#pragma once
#include "UIComponent.h"
#include "LineRenderMaterial.h"

namespace SpartanEngine
{
	class LineRenderComponent : public UIComponent
	{
	public:
		LineRenderComponent();
		virtual ~LineRenderComponent();

		void SetColor(Color color);

		void SetStartAndEnd(Vector2 startPos, Vector2 endPos);
		void SetLineWidth(float width);

	private:
		void Initialize(const GameContext& gameContext) override;
		void Draw(const GameContext& gameContext) override;

		void CreateMaterial();
		COMPONENT_EDITOR(LineRenderComponent)

	private:
		static size_t m_LineMatID;
		static UI::LineRenderMaterial* m_pLineRenderer;

		Vector2 m_StartPos;
		Vector2 m_EndPos;
		Color m_Color;
		float m_LineWidth;
	};
}