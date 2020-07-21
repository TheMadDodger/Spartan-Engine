#include "stdafx.h"
#include "EditorWindow.h"

namespace Spartan::Editor
{
	std::vector<EditorWindow*> EditorWindow::m_pActiveEditorWindows = std::vector<EditorWindow*>();
	std::vector<EditorWindow*> EditorWindow::m_pClosingEditorWindows = std::vector<EditorWindow*>();

	EditorWindow::EditorWindow(const std::string& windowName, float windowWidth, float windowHeight) : m_WindowName(windowName), m_WindowDimensions(windowWidth, windowHeight), m_IsOpen(true), m_Resizeable(true)
	{
	}

	EditorWindow::~EditorWindow()
	{
	}

	void EditorWindow::Close()
	{
		m_pClosingEditorWindows.push_back(this);
	}

	void EditorWindow::RenderGUI()
	{
		OnPaint();

		ImGuiWindowFlags window_flags = m_Resizeable? ImGuiWindowFlags_::ImGuiWindowFlags_NoResize : 0;
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

	void EditorWindow::Cleanup()
	{
		std::for_each(m_pActiveEditorWindows.begin(), m_pActiveEditorWindows.end(), [&](EditorWindow* pWindow)
			{
				delete pWindow;
			});

		m_pActiveEditorWindows.clear();
		m_pClosingEditorWindows.clear();
	}
}