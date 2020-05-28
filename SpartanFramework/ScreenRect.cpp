#include "stdafx.h"
#include "ScreenRect.h"
#include "Mesh.h"
#include "Material.h"
#include "MaterialManager.h"
#include "RenderTexture.h"
#include "PostProcessingStack.h"

namespace SpartanEngine
{
	ScreenRect::ScreenRect() : m_pScreenRenderMaterial(nullptr), m_ScreenQuadVertexbufferID(NULL), m_ScreenQuadVertexArrayID(NULL)
	{
		static const GLfloat g_quad_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
		};

		glGenVertexArrays(1, &m_ScreenQuadVertexArrayID);
		Utilities::Debug::LogGLError(glGetError());
		glBindVertexArray(m_ScreenQuadVertexArrayID);
		Utilities::Debug::LogGLError(glGetError());

		glGenBuffers(1, &m_ScreenQuadVertexbufferID);
		Utilities::Debug::LogGLError(glGetError());
		glBindBuffer(GL_ARRAY_BUFFER, m_ScreenQuadVertexbufferID);
		Utilities::Debug::LogGLError(glGetError());
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
		Utilities::Debug::LogGLError(glGetError());

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		Utilities::Debug::LogGLError(glGetError());

		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		Utilities::Debug::LogGLError(glGetError());

		glEnableVertexAttribArray(0);
		Utilities::Debug::LogGLError(glGetError());

		glBindVertexArray(NULL);
		Utilities::Debug::LogGLError(glGetError());

		size_t matID = MaterialManager::CreateMaterial<Material>("./Resources/Shaders/ScreenRenderer.fx");
		m_pScreenRenderMaterial = MaterialManager::GetMaterial(matID);
	}

	ScreenRect::~ScreenRect()
	{
		glDeleteVertexArrays(1, &m_ScreenQuadVertexArrayID);
		glDeleteBuffers(1, &m_ScreenQuadVertexbufferID);
	}

	void ScreenRect::RenderScreen(Renderer* pRenderer)
	{
		glDisable(GL_DEPTH_TEST);

		// PP Stack
		PostProcessingStack::GetInstance()->RenderPP(this, RenderTexture::GetDefaultRenderTexture());

		// Clear background
		RenderTexture::StartFinalRender();
		pRenderer->ClearBackground();

		// Set material
		m_pScreenRenderMaterial->Use();
		m_pScreenRenderMaterial->SetTexture("ScreenTexture", PostProcessingStack::GetInstance()->GetFinalTexture()->m_GLTextureID);

		// Draw the screen mesh
		DrawScreenMesh();

		// Now render UI on top
		Material::Reset();
		m_pScreenRenderMaterial->Use();
		m_pScreenRenderMaterial->SetTexture("ScreenTexture", RenderTexture::GetUIRenderTexture()->m_GLTextureID);
		DrawScreenMesh();

		// Reset render textures and materials
		RenderTexture::EndFinalRender();
		Material::Reset();

		// Clear the UI Texture
		RenderTexture::GetUIRenderTexture()->Use();
		pRenderer->ClearBackground(true);
		RenderTexture::GetUIRenderTexture()->StopUse();

		glEnable(GL_DEPTH_TEST);
	}

	void ScreenRect::DrawScreenMesh()
	{
		glBindVertexArray(m_ScreenQuadVertexArrayID);
		Utilities::Debug::LogGLError(glGetError());

		// Draw the triangles !
		glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles
		Utilities::Debug::LogGLError(glGetError());

		glBindVertexArray(NULL);
		Utilities::Debug::LogGLError(glGetError());
	}
}