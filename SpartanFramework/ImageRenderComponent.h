#pragma once
#include "BaseComponent.h"
#include <string>

class ImageRenderComponent : public BaseComponent
{
public:
	ImageRenderComponent();
	ImageRenderComponent(const std::string &assetFile);
	ImageRenderComponent(TextureData *pTexture);
	~ImageRenderComponent();

	void SetTexture(TextureData *pTexture);
	void SetColor(const Color &color);
	std::string m_AssetFile = "";

	COMPONENT_EDITOR(ImageRenderComponent)

private:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	//const char* m_AssetFile = nullptr;
	TextureData *m_pImage = nullptr;
	Color m_Color = Color::White();
};

