#pragma once
#include "BaseComponent.h"
#include <string>

class ImageRenderComponent : public BaseComponent
{
public:
	ImageRenderComponent(const char *assetFile);
	~ImageRenderComponent();

	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	const char* m_AssetFile;
	TextureData *m_pImage = nullptr;
};

