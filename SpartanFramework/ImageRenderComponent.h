#pragma once
#include "BaseComponent.h"
#include <string>

class ImageRenderComponent : public BaseComponent
{
public:
	ImageRenderComponent();
	~ImageRenderComponent();

	void SetTexture(TextureData *pTexture);
	TextureData *GetTexture();
	void SetColor(const Color &color);
	std::string m_AssetFile = "";

	Color m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);

private:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

	COMPONENT_EDITOR(ImageRenderComponent)

private:
	//const char* m_AssetFile = nullptr;
	TextureData *m_pImage = nullptr;
};

