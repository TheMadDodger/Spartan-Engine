#pragma once

#include <BaseGame.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/matrix_transform_2d.hpp>

class Blackboard;

class GameApp : public SpartanEngine::BaseGame
{
public:
	GameApp(const SpartanEngine::GameSettings &settings);
	~GameApp();

	// User defined application methods
	void Initialize(const SpartanEngine::GameContext &gameContext) override;
	void GameUpdate(const SpartanEngine::GameContext &gameContext) override;
	void GamePaint(const SpartanEngine::GameContext &gameContext) override;

	virtual void RegisterPrefabs(std::vector<SpartanEngine::GameObject*> &) override {};

private:
	//Material *m_Material;

	//glm::mat4 m_Projection;
	//glm::mat4 m_View;

	//bool m_UseGLM = true;
};

