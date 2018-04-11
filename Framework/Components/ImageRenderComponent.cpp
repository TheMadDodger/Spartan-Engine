#include "stdafx.h"
#include "../../stdafx.h"
#include "ImageRenderComponent.h"
#include "../Content/ContentManager.h"
#include "../Scenes/GameObject.h"
#include "TransformComponent.h"

ImageRenderComponent::ImageRenderComponent(const char *assetFile) : m_AssetFile(assetFile)
{
}

ImageRenderComponent::~ImageRenderComponent()
{
}

void ImageRenderComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	m_pImage = ContentManager::GetInstance()->Load<TextureData>(std::string(m_AssetFile));
}

void ImageRenderComponent::Update(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void ImageRenderComponent::Draw(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	// Apply Transformation from TransformComponent
	glPushMatrix();
	GetGameObject()->GetTransform()->ApplyTransform();
	gameContext.pRenderer->RenderTexture(m_pImage);
	glPopMatrix();
}

