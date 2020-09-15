#pragma once
#include "EditorWindow.h"

namespace Spartan::Editor
{
	class EditorPreferencesWindow : public EditorWindowTemplate<EditorPreferencesWindow>
	{
	public:
		EditorPreferencesWindow();
		virtual ~EditorPreferencesWindow();

	private:
		virtual void OnGUI() override;
		void UpdateTheme();
		void AppearanceTab();

	private:
		static int m_ThemeIndex;
	};
}