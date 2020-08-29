#pragma once
#include "Event.h"
#include "UIObject.h"
#include "TextureData.h"
#include "ImageRenderComponent.h"

namespace Spartan
{
	namespace UI
	{
		class UIButton : public UIObject
		{
		public:
			UIButton();
			virtual ~UIButton();

			BASIC_OBJECT(UIButton, GameObject);

			void Select();
			void Unselect();

			bool IsMouseOver();
			bool IsClicked();
			void SetButtonID(int ID);
			int GetButtonID();

			void DisableButton(bool disable);

			void SetClickBoxSize(const Vector2& size);

			void SetTextures(TextureData* pIdleTexture, TextureData* pMouseOverTexture, TextureData* pMouseClicktexture, TextureData* pSelectedTexture);
			ImageRenderComponent* GetImage();

			Event<UIButton*> ButtonClicked;
			Event<UIButton*> ButtonReleased;
			Event<UIButton*> MouseOver;
			Event<UIButton*> MouseLeave;

		private:
			virtual void Initialize(const GameContext& gameContext) override;
			virtual void Update(const GameContext& gameContext) override;
			virtual void Draw(const GameContext& gameContext) override;
			virtual void UIHandleMouse(const Vector2& relativeMousePos) override;
			virtual void OnResize(const Vector2& newDimensions) override;

		protected:
			enum ButtonState
			{
				Idle,
				Hover,
				Clicked,
			};

			bool m_WasClickedThisFrame;
			bool m_MouseClicked;
			bool m_MouseOver;
			bool m_WasMouseOverLastFrame;
			bool m_Selected;
			bool m_WasSelected;
			bool m_ButtonDisabled = false;
			int m_ButtonID = -1;

		private:
			TextureData* m_pIdleTexture = nullptr;
			TextureData* m_pMouseOverTexture = nullptr;
			TextureData* m_pClickTexture = nullptr;
			TextureData* m_pSelectedTexture = nullptr;

			TextureData* m_pCurrentTexture = nullptr;
			Vector2 m_Size;
			ImageRenderComponent* m_pImageRenderer = nullptr;
		};
	}
}