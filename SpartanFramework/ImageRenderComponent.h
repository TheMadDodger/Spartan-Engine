#pragma once
#include "BaseComponent.h"
#include <string>

class ImageRenderComponent : public BaseComponent
{
public:
	ImageRenderComponent();
	ImageRenderComponent(const char *assetFile);
	ImageRenderComponent(TextureData *pTexture);
	~ImageRenderComponent();

	void SetTexture(TextureData *pTexture);
	char m_AssetFile[100] = "";

	virtual BaseComponent *Create() { return new ImageRenderComponent(""); }

	COMPONENT_EDITOR

private:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	//const char* m_AssetFile = nullptr;
	TextureData *m_pImage = nullptr;
};
