#include "stdafx.h"
#include "EditorPreferencesWindow.h"

namespace Spartan::Editor
{
	int EditorPreferencesWindow::m_ThemeIndex = 0;

	EditorPreferencesWindow::EditorPreferencesWindow() : EditorWindowTemplate("Preferences", 600.0f, 400.0f)
	{
		m_Resizeable = false;
	}

	EditorPreferencesWindow::~EditorPreferencesWindow()
	{
	}

	void EditorPreferencesWindow::OnGUI()
	{
		int current = m_ThemeIndex;
		ImGui::Combo("Editor Skin", &m_ThemeIndex, "Dark\0Classic\0Light\0\0");
		if (current != m_ThemeIndex) UpdateTheme();
	}
	void EditorPreferencesWindow::UpdateTheme()
	{
		switch (m_ThemeIndex)
		{
		case 0:
			ImGui::StyleColorsDark();
			break;
		case 1:
			ImGui::StyleColorsClassic();
			break;
		case 2:
			ImGui::StyleColorsLight();
			break;
		default:
			break;
		}
	}
}