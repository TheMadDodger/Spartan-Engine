#include "stdafx.h"
#include "UIRenderMaterial.h"

namespace SpartanEngine
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

        void UIRenderMaterial::SetShaderVars(BaseComponent*)
        {
            SetMatrix4("WorldProjection", &m_WorldProjection.m[0][0]);
            SetVec4("CenterOffsets", m_CenterOffsets);
            SetTexture("UITexture", m_pTexture);
        }
    }
}