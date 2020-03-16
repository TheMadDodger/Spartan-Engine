#pragma once
#include "GameObject.h"
class UIObject : public GameObject
{
public:
	void Initialize(const GameContext& gameContext) override;
	void Update(const GameContext& gameContext) override;
	void Draw(const GameContext& gameContext) override;
};
