#include "stdafx.h"
#include "UIButton.h"
#include "InputManager.h"
#include "GameScene.h"
#include "Components.h"
#include "Framework.h"

namespace SpartanEngine
{
	namespace UI
	{
		UIButton::UIButton() : m_Size(10.f, 10.f), m_WasClickedThisFrame(false), m_MouseClicked(false), m_MouseOver(false), m_WasMouseOverLastFrame(false), m_Selected(false),
			m_WasSelected(false), m_ButtonDisabled(false)
		{
			m_pImageRenderer = CreateDefaultComponent<ImageRenderComponent>();

			SetName("UIButton");
		}

		UIButton::~UIButton()
		{
		}

		void UIButton::Select()
		{
			m_Selected = true;
		}

		void UIButton::Unselect()
		{
			m_Selected = false;
		}

		bool UIButton::IsMouseOver()
		{
			return m_MouseOver;
		}

		bool UIButton::IsClicked()
		{
			return m_MouseClicked;
		}

		void UIButton::SetButtonID(int ID)
		{
			m_ButtonID = ID;
		}

		int UIButton::GetButtonID()
		{
			return m_ButtonID;
		}

		void UIButton::DisableButton(bool disable)
		{
			m_ButtonDisabled = disable;
		}

		void UIButton::SetClickBoxSize(const Vector2& size)
		{
			m_Size = size;
		}

		void UIButton::SetTextures(TextureData* pIdleTexture, TextureData* pMouseOverTexture, TextureData* pMouseClicktexture, TextureData* pSelectedTexture)
		{
			m_pIdleTexture = pIdleTexture;
			m_pMouseOverTexture = pMouseOverTexture;
			m_pClickTexture = pMouseClicktexture;
			m_pSelectedTexture = pSelectedTexture;

			m_pCurrentTexture = m_pIdleTexture;
			m_pImageRenderer->SetTexture(m_pCurrentTexture);
		}

		ImageRenderComponent* UIButton::GetImage()
		{
			return m_pImageRenderer;
		}

		void UIButton::Initialize(const GameContext&)
		{
			m_WasClickedThisFrame = false;

			m_pCurrentTexture = m_pIdleTexture;
			m_pImageRenderer->SetTexture(m_pCurrentTexture);
		}

		void UIButton::Update(const GameContext& gameContext)
		{
			if (m_ButtonDisabled)
			{
				m_MouseClicked = false;
				m_MouseOver = false;
				m_WasClickedThisFrame = false;
				m_pCurrentTexture = m_pIdleTexture;
				m_pImageRenderer->SetTexture(m_pCurrentTexture);
				return;
			}

			m_MouseClicked = false;
			auto mousePos = gameContext.pInput->GetMouseScreenPosition();

			auto pos = GetTransform()->GetWorldPosition().xy();
			auto bottomRight = pos + m_Size;

			Vector2 offset = Vector2::Zero();
			if (m_pCurrentTexture)
			{
				offset = m_pCurrentTexture->GetOrigin();
			}

			bool mouseDown = (gameContext.pInput->IsMouseButtonDown(SDL_BUTTON_LEFT));

			if (m_Selected)
			{
				m_pCurrentTexture = m_pSelectedTexture;

				if (!m_WasSelected)
				{
					m_WasSelected = true;
					m_pImageRenderer->SetTexture(m_pCurrentTexture);
				}

				if (m_MouseOver)
				{
					if (mouseDown)
					{
						if (!m_WasClickedThisFrame)
						{
							m_MouseClicked = true;
							m_WasClickedThisFrame = true;
							ButtonClicked(this);
						}
					}
					else
					{
						m_WasClickedThisFrame = false;
					}
				}
				else
				{
					m_WasClickedThisFrame = false;
				}
			}
			else if (m_MouseOver)
			{
				m_pCurrentTexture = m_pMouseOverTexture;

				if (m_WasMouseOverLastFrame)
				{
					MouseOver(this);
					m_WasMouseOverLastFrame = false;
					m_pImageRenderer->SetTexture(m_pCurrentTexture);
				}

				if (mouseDown)
				{
					m_pCurrentTexture = m_pClickTexture;

					if (!m_WasClickedThisFrame)
					{
						m_MouseClicked = true;
						m_WasClickedThisFrame = true;
						ButtonClicked(this);
						m_pImageRenderer->SetTexture(m_pCurrentTexture);
					}
				}
				else
				{
					if (m_WasClickedThisFrame)
					{
						ButtonReleased(this);
						m_WasClickedThisFrame = false;
						m_MouseClicked = false;
						m_pImageRenderer->SetTexture(m_pCurrentTexture);
					}
				}
			}
			else
			{
				m_pCurrentTexture = m_pIdleTexture;

				if (!m_WasMouseOverLastFrame)
				{
					MouseLeave(this);
					m_WasMouseOverLastFrame = true;
					m_pImageRenderer->SetTexture(m_pCurrentTexture);
				}

				if (m_WasSelected)
				{
					m_WasSelected = false;
					m_pImageRenderer->SetTexture(m_pCurrentTexture);
				}
			}

			m_MouseOver = false;

			if (m_pCurrentTexture == nullptr) return;
			SetSize(m_pCurrentTexture->GetDimensions().x, m_pCurrentTexture->GetDimensions().y);

			if (mouseDown)
				m_WasClickedThisFrame = true;
		}

		void UIButton::Draw(const GameContext&)
		{
		}

		void UIButton::UIHandleMouse(const Vector2& relativeMousePos)
		{
			if (m_pCurrentTexture == nullptr) return;
			if (!IsEnabled()) return;

			const Origin& origin = m_pImageRenderer->GetOrigin();
			Vector4 offsets = Math::CalculateOffsets(origin, m_Size);

			auto bottomLeft = Vector2(offsets.x, offsets.y);
			auto topRight = Vector2(offsets.z, offsets.w);

			Matrix4X4 matLocalInverse = GetTransform()->GetLocalTransformMatrix().Inverse();

			Vector4 mousePosVec4 = Vector4(relativeMousePos.x, relativeMousePos.y, 0.0f, 1.0f);
			Vector2 localMousePos = (matLocalInverse * mousePosVec4).xy();

			if (CheckPointInRect(localMousePos, { bottomLeft, topRight }))
			{
				//Utilities::Debug::LogInfo("IN BUTTON!");
				m_MouseOver = true;
				PassUIMouseInputToChildren(localMousePos);
			}
		}

		void UIButton::OnResize(const Vector2& newDimensions)
		{
			m_Size = newDimensions;
		}
	}
}