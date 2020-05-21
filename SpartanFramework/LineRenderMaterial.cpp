#include "stdafx.h"
#include "LineRenderMaterial.h"
#include "UIComponent.h"
#include "Canvas.h"

namespace SpartanEngine
{
	namespace UI
	{
		LineRenderMaterial::LineRenderMaterial(ShaderData* pShader) : UIRenderMaterial(pShader), m_LineWidth(1.0f)
		{
		}

		LineRenderMaterial::~LineRenderMaterial()
		{
		}

		void LineRenderMaterial::SetStartAndEnd(Vector2 startPos, Vector2 endPos)
		{
			m_LineRect.x = startPos.x;
			m_LineRect.y = startPos.y;
			m_LineRect.z = endPos.x;
			m_LineRect.w = endPos.y;
		}

		void LineRenderMaterial::SetLineWidth(float width)
		{
			m_LineWidth = width;
		}

		void LineRenderMaterial::SetShaderVars(BaseComponent* pComponent)
		{
			UIComponent* pUIComp = (UIComponent*)pComponent;
			auto projection = pUIComp->GetGameObject()->GetParentCanvas()->GetUIProjectionMatrix();
			SetMatrix4("WorldProjection", &projection.m[0][0]);
			SetColor("Color", m_Color);
			SetVec4("LineRect", m_LineRect);
			glLineWidth(m_LineWidth);
		}
	}
}