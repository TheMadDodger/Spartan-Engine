#include "stdafx.h"
#include "UICanvas.h"
#include "RenderTexture.h"
#include "Material.h"
#include "MaterialManager.h"
#include "TransformComponent.h"

Material* UICanvas::m_pCanvasRenderer = nullptr;

UICanvas::UICanvas() : GameObject("Canvas"), m_pRenderTexture(nullptr), m_CanvasQuadVertexBufferID(NULL), m_pParentCanvas(nullptr), m_pLastParrent(nullptr)
{
	if (m_pCanvasRenderer == nullptr)
	{
		size_t matID = MaterialManager::CreateMaterial<Material>("./Resources/Shaders/CanvasRenderer.fx");
		m_pCanvasRenderer = MaterialManager::GetMaterial(matID);
	}
}

UICanvas::~UICanvas()
{
	DestroyGLData();
}

void UICanvas::SetSize(int width, int height)
{
	m_Dimensions = IntVector2(width, height);

	if (m_pRenderTexture != nullptr)
	{
		m_pRenderTexture->Resize(width, height);
		DestroyGLData();
		CreateCanvasQuad();
	}
}

void UICanvas::SetRenderMode(const CanvasRenderMode& renderMode)
{
	m_RenderMode = renderMode;
}

const Matrix4X4& UICanvas::GetProjectionMatrix()
{
	// TODO: insert return statement here
}

const CanvasRenderMode& UICanvas::GetRenderMode()
{
	return m_RenderMode;
}

void UICanvas::Initialize(const GameContext& gameContext)
{
	m_pRenderTexture = RenderTexture::CreateRenderTexture(m_Dimensions.x, m_Dimensions.y);
	CreateCanvasQuad();
}

void UICanvas::Update(const GameContext& gameContext)
{
	if (m_pLastParrent != GetParent()) FindParentCanvas();
	CalculateMatrices();
}

void UICanvas::Draw(const GameContext& gameContext)
{
	if (!IsDirty()) return;
	m_pRenderTexture->Use();
	gameContext.pRenderer->ClearBackground();
}

void UICanvas::PostDraw(const GameContext& gameContext)
{
	m_pRenderTexture->StopUse();
	m_pCanvasRenderer->Use();
	m_pCanvasRenderer->SetMatrix("CanvasProjectionMat", &m_CanvasProjectionMatrix.m[0][0]);
	m_pCanvasRenderer->SetTexture("CanvasTexture", m_pRenderTexture->GetTextureID());
	DrawCanvasMesh();
	Material::Reset();
}

void UICanvas::CreateCanvasQuad()
{
	const GLfloat g_quad_vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f,
		(float)m_Dimensions.x, 0.0f, 0.0f,
		0.0f, (float)m_Dimensions.y, 0.0f,
		0.0f, (float)m_Dimensions.y, 0.0f,
		(float)m_Dimensions.x, 0.0f, 0.0f,
		(float)m_Dimensions.x, (float)m_Dimensions.y, 0.0f,
	};

	glGenBuffers(1, &m_CanvasQuadVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_CanvasQuadVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
}

void UICanvas::DestroyGLData()
{
	if (m_CanvasQuadVertexBufferID != NULL) glDeleteBuffers(1, &m_CanvasQuadVertexBufferID);
	m_CanvasQuadVertexBufferID = NULL;
}

void UICanvas::DrawCanvasMesh()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_CanvasQuadVertexBufferID);
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

void UICanvas::FindParentCanvas()
{
	m_pParentCanvas = nullptr;
	m_pLastParrent = GetParent();
	if (m_pLastParrent == nullptr) return;

	GameObject* pParent = m_pLastParrent;
	while (pParent != nullptr)
	{
		UICanvas* pParentCanvas = dynamic_cast<UICanvas*>(pParent);
		if (pParentCanvas != nullptr)
		{
			m_pParentCanvas = pParentCanvas;
			m_pParentCanvas->SetDirty();
			break;
		}
		pParent = pParent->GetParent();
	}
}

void UICanvas::CalculateMatrices()
{
	if (m_pParentCanvas)
	{
		//m_pParentCanvas->m_CanvasProjectionMatrix
		return;
	}
	IntVector2 renderWindow = RenderTexture::GetDefaultRenderTexture()->GetDimensions();
	Vector3 gameWindow = Vector3((float)renderWindow.x, (float)renderWindow.y, 1.0f);
	Vector3 canvasSize = Vector3((float)m_Dimensions.x, (float)m_Dimensions.y, 1.0f);

	Vector3 scaleCanvasToRenderTexture = gameWindow / canvasSize;

	Matrix4X4 scaleToRenderTargetMatrix = Matrix4X4::CreateScalingMatrix(scaleCanvasToRenderTexture);
	m_CanvasMatrix = (Matrix4X4)GetTransform()->GetLocalTransformMatrix() * scaleToRenderTargetMatrix;

	auto view = Vector3(gameWindow.x, gameWindow.y, 1.0f);
	m_ProjectionMatrix = Matrix4X4::CreateScalingMatrix(view / 2.0f);
	m_CanvasProjectionMatrix = m_CanvasMatrix * m_ProjectionMatrix;
}
