#pragma once
#include <Framework/Scenes/GameObject.h>

class EditorObject : public GameObject
{
public:
	EditorObject();
	virtual ~EditorObject();

private:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;
};

