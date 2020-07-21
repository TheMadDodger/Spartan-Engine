// EditorTestApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "TestEditor.h"
#include <../EngineTestApp/GameApp.h>

int main(int argc, char* argv[])
{
	// Memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create Game
	Spartan::GameSettings settings;
	settings.AppName = "Orbis Sepia: The End Of Worlds";

	settings.EnableVSync = false;
	settings.Fullscreen = false;
	settings.Window.Width = 1920;
	settings.Window.Height = 1080;
	settings.FullscreenMode = Spartan::FullscreenMode::Borderless;

	auto pGame = new GameApp(settings);

	// Create Editor
	auto pEditor = new TestEditor(pGame);

	// Run the editor
	pEditor->Run();
	delete pEditor;
	return 0;
}
