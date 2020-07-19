#pragma once
#include <GameObject.h>

class EditorObject : public Spartan::GameObject
{
public:
	EditorObject();
	virtual ~EditorObject();

private:
	void Initialize(const Spartan::GameContext &gameContext) override;
	void Update(const Spartan::GameContext &gameContext) override;
	void Draw(const Spartan::GameContext &gameContext) override;
};

