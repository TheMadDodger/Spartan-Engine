#pragma once
#include <GameScene.h>
class BufferTest : public SpartanEngine::GameScene
{
public:
	BufferTest();
	~BufferTest();

private:
	void Initialize(const SpartanEngine::GameContext& gameContext) override;
	void Update(const SpartanEngine::GameContext &gameContext) override;
	void Draw(const SpartanEngine::GameContext &gameContext) override;
};

