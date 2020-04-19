#include "stdafx.h"
#include "ImageRenderComponent.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "UIRenderMaterial.h"

ImageRenderComponent::ImageRenderComponent() : m_AssetFile(""), UIComponent("Image"), m_pImage(nullptr)
{
}

ImageRenderComponent::~ImageRenderComponent()
{
}

void ImageRenderComponent::SetTexture(TextureData *pTexture)
{
	m_pImage = pTexture;
}

TextureData *ImageRenderComponent::GetTexture()
{
	return m_pImage;
}

void ImageRenderComponent::SetColor(const Color & color)
{
	m_Color = color;
}

void ImageRenderComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	if (!m_pImage && m_AssetFile != "")
	{
		m_pImage = ContentManager::GetInstance()->Load<TextureData>(m_AssetFile);
	}
}

void ImageRenderComponent::Update(const GameContext &gameContext)
{
	if (!m_pImage)
	{
		if(ContentManager::FileExists(m_AssetFile))
			m_pImage = ContentManager::GetInstance()->Load<TextureData>(m_AssetFile);
	}
	/*else if (m_pImage->GetFile() != m_AssetFile)
	{
		m_pImage = nullptr;
	}*/

	UNREFERENCED_PARAMETER(gameContext);
}

void ImageRenderComponent::Draw(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	/*if (m_pImage)
	{
		if (m_Color == Color::White())
			gameContext.pRenderer->RenderTexture(m_pImage);
		else
			gameContext.pRenderer->RenderTexture(m_pImage, m_Color);
	}*/

	m_pUIRenderer->SetUITexture(m_pImage);
	m_pUIRenderer->SetAllignment(Origin::TopLeft);
}

