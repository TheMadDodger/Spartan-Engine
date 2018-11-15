#include "stdafx.h"
#include "../../stdafx.h"
#include "ImageRenderComponent.h"
#include "../Content/ContentManager.h"
#include "../Scenes/GameObject.h"
#include "TransformComponent.h"

ImageRenderComponent::ImageRenderComponent(const char *assetFile) : m_AssetFile(assetFile)
{
}

ImageRenderComponent::ImageRenderComponent(TextureData *pTexture) : m_pImage(pTexture)
{
}

ImageRenderComponent::~ImageRenderComponent()
{
}

void ImageRenderComponent::SetTexture(TextureData * pTexture)
{
	m_pImage = pTexture;
}

void ImageRenderComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	if (!m_pImage && m_AssetFile)
	{
		m_pImage = ContentManager::GetInstance()->Load<TextureData>(std::string(m_AssetFile));
	}
}

void ImageRenderComponent::Update(const GameContext &gameContext)
{
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
		gameContext.pRenderer->RenderTexture(m_pImage);
		glPopMatrix();
	}
}

