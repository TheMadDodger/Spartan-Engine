#include "stdafx.h"
#include "ImageRenderComponent.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

ImageRenderComponent::ImageRenderComponent() : m_AssetFile(""), BaseComponent("Image"), m_pImage(nullptr)
{
}

ImageRenderComponent::ImageRenderComponent(const std::string &assetFile) : m_AssetFile(assetFile), BaseComponent("Image"), m_pImage(nullptr)
{
	//memcpy(m_AssetFile, assetFile, strlen(assetFile));
}

ImageRenderComponent::ImageRenderComponent(TextureData *pTexture) : m_pImage(pTexture)
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
	if (m_pImage)
	{
		// Apply Transformation from TransformComponent
		glPushMatrix();
		GetGameObject()->GetTransform()->ApplyTransform();
		if (m_Color == Color::White())
			gameContext.pRenderer->RenderTexture(m_pImage);
		else
			gameContext.pRenderer->RenderTexture(m_pImage, m_Color);
		glPopMatrix();
	}
}

