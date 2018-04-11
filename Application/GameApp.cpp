#include "stdafx.h"
#include "../stdafx.h"
#include "GameApp.h"
#include "../Framework/Content/ContentManager.h"
#include "../Framework/Scenes/SceneManager.h"
#include "Scenes/TestScene.h"

GameApp::GameApp(const GameSettings &settings) : BaseGame(settings)
{
}

GameApp::~GameApp()
{
}

void GameApp::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	SceneManager::GetInstance()->AddScene(new TestScene());
}

void GameApp::GameUpdate(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void GameApp::GamePaint(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
