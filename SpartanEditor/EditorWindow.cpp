#include "stdafx.h"
#include "EditorWindow.h"

namespace Spartan::Editor
{
	std::vector<EditorWindow*> EditorWindow::m_pActiveEditorWindows = std::vector<EditorWindow*>();
	std::vector<EditorWindow*> EditorWindow::m_pClosingEditorWindows = std::vector<EditorWindow*>();

	void EditorWindow::Close()
	{
		m_pClosingEditorWindows.push_back(this);
	}

	void EditorWindow::RenderGUI()
	{
		OnPaint();

		ImGuiWindowFlags window_flags = 0;
		ImGui::SetNextWindowSize(m_WindowDimensions);

		ImGui::Begin(m_WindowName.c_str(), &m_IsOpen, window_flags);
		OnGUI();
		m_WindowDimensions = ImGui::GetWindowSize();
		ImGui::End();

		if (!m_IsOpen) Close();
	}

	void EditorWindow::RenderWindows()
	{
		std::for_each(m_pClosingEditorWindows.begin(), m_pClosingEditorWindows.end(), [&](EditorWindow* pWindow)
			{
				auto it = std::find(m_pActiveEditorWindows.begin(), m_pActiveEditorWindows.end(), pWindow);
				m_pActiveEditorWindows.erase(it);
				delete pWindow;
			});

		m_pClosingEditorWindows.clear();

		std::for_each(m_pActiveEditorWindows.begin(), m_pActiveEditorWindows.end(), [&](EditorWindow* pWindow)
			{
				pWindow->RenderGUI();
			});
	}
}