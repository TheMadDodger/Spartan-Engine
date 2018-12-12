#pragma once
#include <GameScene.h>

class TestScene2 : public GameScene
{
public:
	TestScene2() : GameScene("Test Scene 2") {}
	~TestScene2();

	void Initialize(const GameContext &gameContext) override;
	void PostInitialize(const GameContext &gameContext) override;

	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	TextureData *m_pBitmap = nullptr;
	GameObject *m_pObject;
	GameObject *m_pImage = nullptr;
	GameObject *m_pAudioSource = nullptr;
	GameObject *m_pSpriteSheetTest = nullptr;

	GameObject *m_pGroundBox = nullptr;
};

