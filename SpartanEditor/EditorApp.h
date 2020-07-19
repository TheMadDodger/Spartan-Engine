#pragma once
#include <BaseGame.h>
#include "EditorWindow.h"

namespace Spartan::Editor
{
	class EditorApp
	{
	public:
		EditorApp(BaseGame* pGame);
		virtual ~EditorApp();

		void Run();

	protected:
		virtual void RegisterUserWindows(std::vector<EditorWindow*>& userWindows) = 0;

	private:
		void Initialize();
		void Tick();
		void Paint();
		void Cleanup();

	private:
		BaseGame* m_pGame;
		bool m_IsRunning;
	};
}