#include "stdafx.h"
#include "UIRenderMaterial.h"

namespace Spartan
{
    namespace UI
    {
        UIRenderMaterial::UIRenderMaterial(ShaderData* pShader) : Material(pShader), m_pTexture(nullptr), m_CenterOffsets()
        {
        }

        UIRenderMaterial::~UIRenderMaterial()
        {
        }

        void UIRenderMaterial::SetUITexture(TextureData* pTexture)
        {
            m_pTexture = pTexture;
        }

        void UIRenderMaterial::SetWorldProjection(const Matrix4X4& worldProjection)
        {
            m_WorldProjection = worldProjection;
        }

        void UIRenderMaterial::SetOffsets(const Vector4& offsets)
        {
            m_CenterOffsets = offsets;
        }

		void UIRenderMaterial::SetUIColor(const Color& color)
		{
            m_Color = color;
		}

        void UIRenderMaterial::SetShaderVars(BaseComponent*)
        {
            SetMatrix4("WorldProjection", &m_WorldProjection.m[0][0]);
            SetVec4("CenterOffsets", m_CenterOffsets);
            SetColor("Color", m_Color);
            SetTexture("UITexture", m_pTexture);
        }
    }
}