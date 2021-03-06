// EngineTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameApp.h"

int main(int argc, char *argv[])
{
	// Memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	{
		// Create game
		GameSettings settings;
		settings.AppName = "Spartan Editor";
		settings.EnableVSync = false;

		settings.Window.Width = 1920;
		settings.Window.Height = 1020;

		auto pGame = new GameTool(settings);

		// Initialisation of game
		auto init = pGame->RootInitialize();
		if (!init) return EXIT_FAILURE;

		bool running = true;

		// Game Loop
		while (running)
		{
			running = pGame->RootGameUpdate();
			pGame->RootGamePaint();
		}

		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		delete pGame;
	}

    return 0;
}

