#include "stdafx.h"
#include "EditorApp.h"
#include <SceneManager.h>
#include "SceneWindow.h"

namespace Spartan::Editor
{
	EditorApp::EditorApp(BaseGame* pGame) : m_pGame(pGame), m_IsRunning(false)
	{
	}

	EditorApp::~EditorApp()
	{
		delete m_pGame;
	}

	void EditorApp::Initialize()
	{
		m_pGame->RootInitialize();
		m_IsRunning = true;
	}

	void EditorApp::Tick()
	{

	}

	void EditorApp::Cleanup()
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void EditorApp::Run()
	{
		Initialize();
		while (m_IsRunning)
		{
			Tick();
			Paint();
		}
		Cleanup();
	}

	void EditorApp::Paint()
	{
		// Clear the background
		m_pGame->GetGameContext().pRenderer->ClearBackground();

		// Draw editors
		EditorWindow::RenderWindows();

		// Draw scenes
		//Spartan::SceneManager::GetInstance()->Draw(m_GameContext);

		// Update window
		SDL_GL_SwapWindow(m_pGame->GetGameContext().pRenderer->GetWindow());

		// Render to the screen
		m_pGame->GetGameContext().pRenderer->RenderEnd();
	}
}