#pragma once
#include "Event.h"
#include "UIObject.h"

class TextureData;
class ImageRenderComponent;

class UIButton : public UIObject
{
public:
	UIButton();
	virtual ~UIButton();

	void Select();
	void Unselect();

	bool IsMouseOver();
	bool IsClicked();
	void SetButtonID(int ID);
	int GetButtonID();

	void DisableButton(bool disable);

	void SetClickBoxSize(const Vector2 &size);

	void SetTextures(TextureData *pIdleTexture, TextureData *pMouseOverTexture, TextureData *pMouseClicktexture, TextureData *pSelectedTexture);

	Event<UIButton*> ButtonClicked;
	Event<UIButton*> ButtonReleased;
	Event<UIButton*> MouseOver;
	Event<UIButton*> MouseLeave;

protected:
	virtual void OnMouseOver();
	virtual void OnMouseLeave();
	virtual void OnMouseClick();

private:
	virtual void Initialize(const GameContext &gameContext) override;
	virtual void Update(const GameContext &gameContext) override;
	virtual void Draw(const GameContext &gameContext) override;
	virtual void UIHandleMouse(const Vector2& relativeMousePos) override;

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
	TextureData *m_pIdleTexture = nullptr;
	TextureData *m_pMouseOverTexture = nullptr;
	TextureData *m_pClickTexture = nullptr;
	TextureData *m_pSelectedTexture = nullptr;

	TextureData *m_pCurrentTexture = nullptr;
	Vector2 m_Size;
	ImageRenderComponent* m_pImageRenderer = nullptr;
};

