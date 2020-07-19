#include "stdafx.h"
#include "EditorWindow.h"

namespace Spartan::Editor
{
	std::vector<EditorWindow*> EditorWindow::m_pActiveEditorWindows = std::vector<EditorWindow*>();

	void EditorWindow::RenderGUI()
	{
		ImGuiWindowFlags window_flags = 0;
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(m_WindowDimensions);

		ImGui::Begin("Object List", NULL, window_flags);
		OnGUI();
		ImGui::End();
	}

	void EditorWindow::RenderWindows()
	{
		std::for_each(m_pActiveEditorWindows.begin(), m_pActiveEditorWindows.end(), [&](EditorWindow* pWindow)
			{
				pWindow->RenderGUI();
			});
	}
}