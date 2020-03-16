#include "stdafx.h"
#include "ScreenRect.h"
#include "Mesh.h"
#include "Material.h"
#include "MaterialManager.h"
#include "RenderTexture.h"

ScreenRect::ScreenRect() : m_pScreenRenderMaterial(nullptr), m_ScreenQuadVertexbufferID(NULL)
{
	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &m_ScreenQuadVertexbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ScreenQuadVertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	size_t matID = MaterialManager::CreateMaterial<Material>("./Resources/Shaders/ScreenRenderer.fx");
	m_pScreenRenderMaterial = MaterialManager::GetMaterial(matID);
}

ScreenRect::~ScreenRect()
{
	glDeleteBuffers(1, &m_ScreenQuadVertexbufferID);
}

void ScreenRect::RenderScreen(Renderer *pRenderer)
{
	// Clear background
	RenderTexture::StartFinalRender();
	pRenderer->ClearBackground();

	// Set material
	m_pScreenRenderMaterial->Use();
	m_pScreenRenderMaterial->SetTexture("ScreenTexture", RenderTexture::GetDefaultRenderTexture()->m_GLTextureID);
	
	// Draw the screen mesh
	DrawScreenMesh();

	// Reset render textures and materials
	RenderTexture::EndFinalRender();
	Material::Reset();
}

void ScreenRect::DrawScreenMesh()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_ScreenQuadVertexbufferID);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}
