#pragma once

#include <BaseGame.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/matrix_transform_2d.hpp>

class Blackboard;

class GameApp : public BaseGame
{
public:
	GameApp(const GameSettings &settings);
	~GameApp();

	// User defined application methods
	void Initialize(const GameContext &gameContext) override;
	void GameUpdate(const GameContext &gameContext) override;
	void GamePaint(const GameContext &gameContext) override;

	virtual void RegisterPrefabs(std::vector<GameObject*> &) override {};

private:
	//Material *m_Material;

	//glm::mat4 m_Projection;
	//glm::mat4 m_View;

	//bool m_UseGLM = true;
};

