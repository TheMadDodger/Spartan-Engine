#pragma once
#include <GameScene.h>

class Blackboard;

class TestScene : public GameScene
{
public:
	TestScene() : GameScene("Test Scene") {}
	~TestScene();

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

	vector<Vector2> m_Points;

	ParticleSystem *m_pPartSystem;

	GameObject *m_pPartObject;

	Blackboard *m_pBlackboard;
};

