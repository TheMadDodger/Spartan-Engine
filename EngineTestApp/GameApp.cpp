#include "stdafx.h"
#include "GameApp.h"
#include <ContentManager.h>
#include <SceneManager.h>
#include "Scenes/TestScene.h"
#include "Scenes/SkinningTestScene.h"

GameApp::GameApp(const GameSettings &settings) : BaseGame(settings)
{
}

GameApp::~GameApp()
{
}

void GameApp::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	SceneManager::GetInstance()->AddScene(new SkinningTestScene());
}

void GameApp::GameUpdate(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void GameApp::GamePaint(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
