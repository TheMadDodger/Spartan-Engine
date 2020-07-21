#include "stdafx.h"
#include "SceneWindow.h"
#include "EditorApp.h"
#include <SceneManager.h>
#include <GameScene.h>
#include <RenderTexture.h>

namespace Spartan::Editor
{
	SceneWindow::SceneWindow() : EditorWindowTemplate("Scene", 1280.0f, 720.0f), m_pSceneRenderTexture(nullptr)
	{
		m_pSceneCamera = new SceneViewCamera();

		EditorApp::GetEditorApp()->InitializeGameObject(m_pSceneCamera);
		auto settings = BaseGame::GetGame()->GetGameSettings();
	}

	SceneWindow::~SceneWindow()
	{
	}

	void SceneWindow::OnPaint()
	{
		GameScene* pCurrentScene = SceneManager::GetInstance()->GetCurrentScene();
		if (pCurrentScene == nullptr) return;

		CameraComponent* pPreviousCamera = pCurrentScene->GetActiveCamera();
		pCurrentScene->SetActiveCamera(m_pSceneCamera->GetCameraComponent());
		EditorApp::GetEditorApp()->RenderScene();
		pCurrentScene->SetActiveCamera(pPreviousCamera);
	}

	void SceneWindow::OnGUI()
	{
		if (ImGui::IsWindowFocused()) EditorApp::GetEditorApp()->UpdateGameObject(m_pSceneCamera);

		GLsizei w = (GLsizei)m_WindowDimensions.x;
		GLsizei h = (GLsizei)m_WindowDimensions.y;
		float aspect = (float)w / (float)h;

		ImVec2 pos = ImGui::GetCursorScreenPos();
		float width = ImGui::GetWindowWidth();
		float height = width / aspect;
		ImGui::GetWindowDrawList()->AddImage(
			(void*)RenderTexture::GetDefaultRenderTexture()->GetTextureID(), ImVec2(pos.x, pos.y),
			ImVec2(pos.x + width, pos.y + height), ImVec2(0, 1), ImVec2(1, 0));
	}
}