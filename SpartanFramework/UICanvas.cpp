#include "stdafx.h"
#include "UICanvas.h"
#include "RenderTexture.h"
#include "Material.h"
#include "MaterialManager.h"
#include "TransformComponent.h"
#include "InputManager.h"

Material* UICanvas::m_pCanvasRenderer = nullptr;

UICanvas::UICanvas() : UIObject("Canvas"), m_pRenderTexture(nullptr), m_CanvasQuadVertexBufferID(NULL), m_pLastParrent(nullptr)
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

	Vector3 canvasSize = Vector3((float)m_Dimensions.x, (float)m_Dimensions.y, 2.0f);
	m_UIProjectionMatrix = Matrix4X4::CreateTranslationMatrix(canvasSize / -2.0f) * Matrix4X4::CreateScalingMatrix(canvasSize / 2.0f).Inverse();
}

void UICanvas::SetRenderMode(const CanvasRenderMode& renderMode)
{
	m_RenderMode = renderMode;
}

const Matrix4X4& UICanvas::GetProjectionMatrix()
{
	// TODO: insert return statement here
	return m_ProjectionMatrix;
}

const CanvasRenderMode& UICanvas::GetRenderMode()
{
	return m_RenderMode;
}

const Matrix4X4& UICanvas::GetUIProjectionMatrix()
{
	return m_UIProjectionMatrix;
}

void UICanvas::Initialize(const GameContext& gameContext)
{
	m_pRenderTexture = RenderTexture::CreateRenderTexture(m_Dimensions.x, m_Dimensions.y, false);
	CreateCanvasQuad();
}

void UICanvas::Update(const GameContext& gameContext)
{
	CalculateMatrices();

	if (m_pParentCanvas == nullptr)
	{
		auto mousePos = gameContext.pInput->GetMouseScreenPosition();
		UIHandleMouse(mousePos, gameContext);
	}
}

void UICanvas::Draw(const GameContext& gameContext)
{
	if (!IsDirty()) return;
	m_pRenderTexture->Use();
	gameContext.pRenderer->ClearBackground(true);
}

void UICanvas::PostDraw(const GameContext& gameContext)
{
	m_pRenderTexture->StopUse();
	m_pCanvasRenderer->Use();
	m_pCanvasRenderer->SetMatrix4("CanvasProjectionMat", &m_CanvasProjectionMatrix.m[0][0]);
	m_pCanvasRenderer->SetTexture("CanvasTexture", m_pRenderTexture->GetTextureID());
	DrawCanvasMesh();
	Material::Reset();
}

void UICanvas::OnParentUpdated(GameObject* pNewParent)
{
	GameObject* pParent = GetParent();
	while (pParent != nullptr)
	{
		UICanvas* pCanvas = dynamic_cast<UICanvas*>(pParent);
		if (pCanvas != nullptr)
		{
			m_pParentCanvas = pCanvas;
			return;
		}
	}
	m_pParentCanvas = nullptr;
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

void UICanvas::CalculateMatrices()
{
	if (m_pParentCanvas)
	{
		//m_pParentCanvas->m_CanvasProjectionMatrix
		return;
	}

	IntVector2 renderWindow = RenderTexture::GetDefaultRenderTexture()->GetDimensions();
	Vector3 gameWindow = Vector3((float)renderWindow.x, (float)renderWindow.y, 2.0f);
	m_CanvasMatrix = (Matrix4X4)GetTransform()->GetLocalTransformMatrix();
	auto view = Vector3(gameWindow.x, gameWindow.y, 2.0f);
	m_ProjectionMatrix = Matrix4X4::CreateScalingMatrix(view / 2.0f);
	m_CanvasProjectionMatrix =  m_CanvasMatrix * Matrix4X4::CreateTranslationMatrix(view / -2.0f) * m_ProjectionMatrix.Inverse();
}

void UICanvas::UIHandleMouse(const Vector2& relativeMousePos, const GameContext& gameContext)
{
	auto topLeft = Vector2(0.0f, 0.0f);
	auto bottomRight = Vector2((float)m_Dimensions.x, (float)m_Dimensions.y);

	Matrix4X4 matLocalInverse = GetTransform()->GetLocalTransformMatrix().Inverse();

	Vector4 mousePosVec4 = Vector4(relativeMousePos.x, relativeMousePos.y, 0.0f, 1.0f);
	Vector2 localMousePos = (matLocalInverse * mousePosVec4).xy();

	//Utilities::Debug::LogInfo("Relative: " + to_string(relativeMousePos.x) + ", " + to_string(relativeMousePos.y) + ", Local: " + to_string(localMousePos.x) + ", " + to_string(localMousePos.y));

	if (CheckPointInRect(localMousePos, { topLeft, bottomRight }))
	{
		//Utilities::Debug::LogInfo("IN CANVAS!");
		std::for_each(m_pChildren.begin(), m_pChildren.end(), [&](GameObject* pChild) {pChild->UIHandleMouse(localMousePos, gameContext); });
	}
}
