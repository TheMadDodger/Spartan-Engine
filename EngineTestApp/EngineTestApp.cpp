// EngineTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameApp.h"

int main(int argc, char *argv[])
{
	// Memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create game
	SpartanEngine::GameSettings settings;
	settings.AppName = "Spartan Framework TEST App";
	settings.EnableVSync = false;

	settings.Window.Width = 1280;
	settings.Window.Height = 720;

	auto pGame = new GameApp(settings);

	// Initialisation of game
	auto init = pGame->RootInitialize();
	if (!init) return EXIT_FAILURE;

	// Game Loop
	while (pGame->RootGameUpdate())
	{
		pGame->RootGamePaint();
	}

	delete pGame;

    return 0;
}

