#pragma once
#include "../../Framework/Scenes/GameScene.h"

class TestScene : public GameScene
{
public:
	TestScene() : GameScene("Test Scene") {}
	~TestScene();

	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	TextureData *m_pBitmap = nullptr;
	GameObject *m_pObject;
	GameObject *m_pImage = nullptr;
	GameObject *m_pAudioSource = nullptr;
	GameObject *m_pSpriteSheetTest = nullptr;
};

