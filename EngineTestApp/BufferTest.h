#pragma once
#include <GameScene.h>
#include <PhysicsObjectComponent.h>

class BufferTest : public SpartanEngine::GameScene
{
public:
	BufferTest();
	~BufferTest();

private:
	void Initialize(const SpartanEngine::GameContext& gameContext) override;
	void Update(const SpartanEngine::GameContext &gameContext) override;
	void Draw(const SpartanEngine::GameContext &gameContext) override;

	size_t m_Mat2;
};

