#pragma once
#include <GameScene.h>
#include <PhysicsObjectComponent.h>

class BufferTest : public Spartan::GameScene
{
public:
	BufferTest();
	~BufferTest();

private:
	void Initialize(const Spartan::GameContext& gameContext) override;
	void Update(const Spartan::GameContext &gameContext) override;
	void Draw(const Spartan::GameContext &gameContext) override;

	size_t m_Mat2;
};

