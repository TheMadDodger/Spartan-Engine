#include "stdafx.h"
#include "ImageRenderComponent.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "UIRenderMaterial.h"

namespace SpartanEngine
{
	ImageRenderComponent::ImageRenderComponent() : UIComponent("Image"), m_pImage(nullptr), m_Offsets()
	{
	}

	ImageRenderComponent::~ImageRenderComponent()
	{
	}

	void ImageRenderComponent::SetTexture(TextureData* pTexture)
	{
		m_pImage = pTexture;
		GetGameObject()->SetDirty();
	}

	void ImageRenderComponent::SetColor(const Color& color)
	{
		m_Color = color;
		GetGameObject()->SetDirty();
	}

	TextureData* ImageRenderComponent::GetTexture()
	{
		return m_pImage;
	}

	void ImageRenderComponent::Update(const GameContext&)
	{
		if (m_pImage == nullptr) return;
		m_Offsets = Math::CalculateOffsets(GetOrigin(), GetGameObject()->GetSize());
	}

	void ImageRenderComponent::Draw(const GameContext&)
	{
		m_pUIRenderer->SetUITexture(m_pImage);
		m_pUIRenderer->SetOffsets(m_Offsets);
	}

	bool ImageRenderComponent::CanRender()
	{
		return m_pImage != nullptr;
	}
}