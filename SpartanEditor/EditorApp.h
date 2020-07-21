#pragma once
#include <BaseGame.h>
#include "EditorWindow.h"

namespace Spartan
{
	class EditorApp
	{
	public:
		EditorApp(BaseGame* pGame);
		virtual ~EditorApp();

		void Run();
		void InitializeGameObject(GameObject* pObject);
		void UpdateGameObject(GameObject* pObject);

		static EditorApp* GetEditorApp();

		void RenderScene();

		void EnterPlayMode();
		void ExitPlayMode();

	protected:
		//virtual void RegisterUserWindows(std::vector<EditorWindow*>& userWindows) = 0;

	private:
		void Initialize();
		void Tick();
		void Paint();
		void Cleanup();

		void HandleWindowEvent(SDL_Event* event);

		void CreateDefaultMainMenuBar();
		void EditorUpdateScene();
		void EditorUpdateObject(GameObject* pObject);

	private:
		BaseGame* m_pGame;
		static EditorApp* m_pEditorApp;
		bool m_IsRunning;
		bool m_PlayModeActive;
		bool m_PlayModePaused;
	};
}