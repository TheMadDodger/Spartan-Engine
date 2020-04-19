#include "stdafx.h"
#include "UIRenderMaterial.h"

UIRenderMaterial::UIRenderMaterial(ShaderData* pShader) : Material(pShader), m_pTexture(nullptr), m_Allignment(Origin::Center)
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

void UIRenderMaterial::SetAllignment(const Origin& allignment)
{
	m_Allignment = allignment;
    Vector2 halfDimensions = m_pTexture->GetDimensions();
    halfDimensions = halfDimensions / 2.0f;

	switch (m_Allignment)
	{
    case Math::TopLeft:
        m_CenterOffsets = Vector4(0.0f, 0.0f, halfDimensions.x * 2.0f, halfDimensions.y * 2.0f);
        break;
    case Math::TopMiddle:
        m_CenterOffsets = Vector4(-halfDimensions.x, 0.0f, halfDimensions.x, halfDimensions.y * 2.0f);
        break;
    case Math::TopRight:
        m_CenterOffsets = Vector4(-halfDimensions.x * 2.0f, 0.0f, 0.0f, halfDimensions.y * 2.0f);
        break;
    case Math::LeftCenter:
        m_CenterOffsets = Vector4(0.0f, -halfDimensions.y, halfDimensions.x * 2.0f, halfDimensions.y);
        break;
    case Math::Center:
        m_CenterOffsets = Vector4(-halfDimensions.x, -halfDimensions.y, halfDimensions.x, halfDimensions.y);
        break;
    case Math::RightCenter:
        m_CenterOffsets = Vector4(halfDimensions.x * 2.0f, -halfDimensions.y, 0.0f, halfDimensions.y * 2.0f);
        break;
    case Math::BottomLeft:
        break;
    case Math::BottomMiddle:
        break;
    case Math::BottomRight:
        break;
    default:
        break;
	}
}

void UIRenderMaterial::SetShaderVars(BaseComponent*)
{
    SetMatrix4("WorldProjection", &m_WorldProjection.m[0][0]);
    SetVec4("CenterOffsets", m_CenterOffsets);
    SetTexture("UITexture", m_pTexture);
}
