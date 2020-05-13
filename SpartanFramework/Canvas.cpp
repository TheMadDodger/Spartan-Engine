#include "stdafx.h"
#include "Canvas.h"
#include "RenderTexture.h"
#include "Material.h"
#include "MaterialManager.h"
#include "TransformComponent.h"
#include "InputManager.h"

namespace SpartanEngine
{
	namespace UI
	{
		Material* Canvas::m_pCanvasRenderer = nullptr;

		Canvas::Canvas() : UIObject("Canvas"), m_pRenderTexture(nullptr), m_CanvasQuadVertexBufferID(NULL), m_pLastParrent(nullptr), m_ResizeToScreen(nullptr), m_Color(Color::White())
		{
			if (m_pCanvasRenderer == nullptr)
			{
#if _DEBUG
				size_t matID = MaterialManager::CreateMaterial<Material>("./Resources/Shaders/CanvasRenderer_debug.fx");
#else
				size_t matID = MaterialManager::CreateMaterial<Material>("./Resources/Shaders/CanvasRenderer.fx");
#endif // _DEBUG
				matID = MaterialManager::CreateMaterial<Material>("./Resources/Shaders/CanvasRenderer.fx");
				m_pCanvasRenderer = MaterialManager::GetMaterial(matID);
			}
		}

		Canvas::~Canvas()
		{
			DestroyGLData();
		}

		void Canvas::SetRenderMode(const CanvasRenderMode& renderMode)
		{
			m_RenderMode = renderMode;
		}

		const Matrix4X4& Canvas::GetProjectionMatrix()
		{
			// TODO: insert return statement here
			return m_ProjectionMatrix;
		}

		const CanvasRenderMode& Canvas::GetRenderMode()
		{
			return m_RenderMode;
		}

		const Matrix4X4& Canvas::GetUIProjectionMatrix()
		{
			return m_UIProjectionMatrix;
		}

		void Canvas::AutoResizeToScreen(bool enable)
		{
			m_ResizeToScreen = enable;
		}

		void Canvas::SetColor(const Color& color)
		{
			m_Color = color;
		}

		void Canvas::RootDraw(const GameContext& gameContext)
		{
			if (IsDirty())
			{
				// User defined Draw()
				Draw(gameContext);

				for (auto pComponent : m_pComponents)
				{
					pComponent->RootDraw(gameContext);
				}

				for (auto pChild : m_pChildren)
				{
					if (pChild->IsEnabled())
						pChild->RootDraw(gameContext);
				}
			}

			PostDraw(gameContext);

			SetDirty(false);
		}

		void Canvas::Initialize(const GameContext& gameContext)
		{
			if (m_ResizeToScreen)
			{
				AutoResizeToScreenControl();
			}

			m_pRenderTexture = RenderTexture::CreateRenderTexture(m_Dimensions.x, m_Dimensions.y, false);
			CreateCanvasQuad();
		}

		void Canvas::Update(const GameContext& gameContext)
		{
			if (m_ResizeToScreen)
			{
				AutoResizeToScreenControl();
			}

			CalculateMatrices();

			if (m_pParentCanvas == nullptr)
			{
				auto mousePos = gameContext.pInput->GetMouseScreenPosition();
				UIHandleMouse(mousePos);
			}
		}

		void Canvas::Draw(const GameContext& gameContext)
		{
			m_pRenderTexture->Use();
			gameContext.pRenderer->ClearBackground(true);
		}

		void Canvas::PostDraw(const GameContext& gameContext)
		{
			if (IsDirty()) m_pRenderTexture->StopUse();

			if (RenderTexture::GetDefaultRenderTexture()->IsInUse()) RenderTexture::GetUIRenderTexture()->Use();

			m_pCanvasRenderer->Use();
			m_pCanvasRenderer->SetMatrix4("CanvasProjectionMat", &m_CanvasProjectionMatrix.m[0][0]);
			m_pCanvasRenderer->SetTexture("CanvasTexture", m_pRenderTexture->GetTextureID());
			m_pCanvasRenderer->SetColor("Color", m_Color);
			DrawCanvasMesh();
			Material::Reset();

			if (RenderTexture::GetUIRenderTexture()->IsInUse()) RenderTexture::GetUIRenderTexture()->StopUse();
		}

		void Canvas::OnParentUpdated(GameObject* pNewParent)
		{
			GameObject* pParent = GetParent();
			while (pParent != nullptr)
			{
				Canvas* pCanvas = dynamic_cast<Canvas*>(pParent);
				if (pCanvas != nullptr)
				{
					m_pParentCanvas = pCanvas;
					return;
				}
				pParent = pParent->GetParent();
			}
			m_pParentCanvas = nullptr;
		}

		void Canvas::CreateCanvasQuad()
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

		void Canvas::DestroyGLData()
		{
			if (m_CanvasQuadVertexBufferID != NULL) glDeleteBuffers(1, &m_CanvasQuadVertexBufferID);
			m_CanvasQuadVertexBufferID = NULL;
		}

		void Canvas::DrawCanvasMesh()
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

		void Canvas::CalculateMatrices()
		{
			IntVector2 renderWindow = RenderTexture::GetDefaultRenderTexture()->GetDimensions();
			Vector3 gameWindow = Vector3((float)renderWindow.x, (float)renderWindow.y, 2.0f);

			if (m_pParentCanvas)
			{
				Vector2 parentSize = m_pParentCanvas->GetSize();
				gameWindow = Vector3(parentSize.x, parentSize.y, 2.0f);
			}

			m_CanvasMatrix = (Matrix4X4)GetTransform()->GetLocalTransformMatrix();
			auto view = Vector3(gameWindow.x, gameWindow.y, 2.0f);
			m_ProjectionMatrix = Matrix4X4::CreateScalingMatrix(view / 2.0f);
			m_CanvasProjectionMatrix = m_CanvasMatrix * Matrix4X4::CreateTranslationMatrix(view / -2.0f) * m_ProjectionMatrix.Inverse();
		}

		void Canvas::AutoResizeToScreenControl()
		{
			IntVector2 renderWindow = RenderTexture::GetDefaultRenderTexture()->GetDimensions();
			SetSize((float)renderWindow.x, (float)renderWindow.y);
		}

		void Canvas::UIHandleMouse(const Vector2& relativeMousePos)
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
				PassUIMouseInputToChildren(localMousePos);
			}
		}

		void Canvas::OnResize(const Vector2& newDimensions)
		{
			if (m_pRenderTexture != nullptr)
			{
				m_pRenderTexture->Resize(newDimensions.x, newDimensions.y);
				DestroyGLData();
				CreateCanvasQuad();
			}

			Vector3 canvasSize = Vector3((float)newDimensions.x, (float)newDimensions.y, 2.0f);
			m_UIProjectionMatrix = Matrix4X4::CreateTranslationMatrix(canvasSize / -2.0f) * Matrix4X4::CreateScalingMatrix(canvasSize / 2.0f).Inverse();
			SetFullDirty();
		}
	}
}