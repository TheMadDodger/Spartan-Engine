#include "stdafx.h"
#include "UIComponent.h"
#include "MaterialManager.h"
#include "UIRenderMaterial.h"
#include "Canvas.h"
#include "UIObject.h"
#include "TransformComponent.h"

namespace Spartan
{
	GLuint UIComponent::m_UIVertexBufferID = 0;
	GLuint UIComponent::m_UIVertexArrayID = 0;
	bool UIComponent::m_DoesVertexBufferExist = false;
	int UIComponent::m_InstanceCount = 0;

	UIComponent::UIComponent(const char* name) : BaseComponent(name), m_pUIRenderer(nullptr), m_Origin(Origin::BottomLeft)
	{
		if (!m_DoesVertexBufferExist)
		{
			static const GLfloat vertexData[] = {
				0.0f, 0.0f, 0.0f,
			};

			glGenVertexArrays(1, &m_UIVertexArrayID);
			Utilities::Debug::LogGLError(glGetError());
			
			glBindVertexArray(m_UIVertexArrayID);
			Utilities::Debug::LogGLError(glGetError());

			glGenBuffers(1, &m_UIVertexBufferID);
			Utilities::Debug::LogGLError(glGetError());
			glBindBuffer(GL_ARRAY_BUFFER, m_UIVertexBufferID);
			Utilities::Debug::LogGLError(glGetError());
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
			Utilities::Debug::LogGLError(glGetError());

			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				3 * sizeof(float),                  // stride
				(void*)0            // array buffer offset
			);
			Utilities::Debug::LogGLError(glGetError());

			glBindBuffer(GL_ARRAY_BUFFER, NULL);
			Utilities::Debug::LogGLError(glGetError());

			glEnableVertexAttribArray(0);
			Utilities::Debug::LogGLError(glGetError());

			glBindVertexArray(NULL);
			Utilities::Debug::LogGLError(glGetError());

			m_DoesVertexBufferExist = true;
		}

		++m_InstanceCount;
	}

	UIComponent::~UIComponent()
	{
		--m_InstanceCount;

		if (m_InstanceCount == 0)
		{
			glDeleteVertexArrays(1, &m_UIVertexArrayID);
			glDeleteBuffers(1, &m_UIVertexBufferID);
			m_DoesVertexBufferExist = false;
		}
	}

	Spartan::UI::UIObject* UIComponent::GetGameObject()
	{
		return static_cast<Spartan::UI::UIObject*>(BaseComponent::GetGameObject());
	}

	void UIComponent::SetOrigin(const Origin& origin)
	{
		if (m_Origin != origin)
			GetGameObject()->SetDirty();

		m_Origin = origin;
	}

	const Origin& UIComponent::GetOrigin()
	{
		return m_Origin;
	}

	void UIComponent::SetCustomMaterial(UI::UIRenderMaterial* pMaterial)
	{
		m_pCustomMaterial = pMaterial;
	}

	bool UIComponent::CanRender()
	{
		return true;
	}

	void UIComponent::RootUpdate(const GameContext& gameContext)
	{
		if (!IsInitialized())
		{
			RootInitialize(gameContext);
		}

		if (!m_bEnabled) return;

		Spartan::UI::UIObject* pObject = GetGameObject();
		Spartan::UI::Canvas* pCanvas = pObject->GetParentCanvas();
		Matrix4X4 uiProjection = pCanvas->GetUIProjectionMatrix();
		Matrix4X4 world = pObject->GetTransform()->GetWorldMatrix();
		m_UIMatrix = world * uiProjection;

		Update(gameContext);
	}

	void UIComponent::RootDraw(const GameContext& gameContext)
	{
		if (!m_bInitialized) return;

		if (!m_bEnabled) return;
		if (!CanRender()) return;

		// User defined Draw()
		m_pUIRenderer = gameContext.pRenderer->GetUIRenderer();
		if (m_pCustomMaterial) 
			m_pUIRenderer = m_pCustomMaterial;

		m_pUIRenderer->Use();
		m_pUIRenderer->SetWorldProjection(m_UIMatrix);
		Draw(gameContext);
		m_pUIRenderer->SetShaderVars(this);
		Render();
		Material::Reset();
	}

	void UIComponent::Render()
	{
		glBindVertexArray(m_UIVertexArrayID);
		Utilities::Debug::LogGLError(glGetError());

		// Draw the point !
		glDrawArrays(GL_POINTS, 0, 1); // 2*3 indices starting at 0 -> 2 triangles
		Utilities::Debug::LogGLError(glGetError());

		glBindVertexArray(NULL);
		Utilities::Debug::LogGLError(glGetError());
	}
}