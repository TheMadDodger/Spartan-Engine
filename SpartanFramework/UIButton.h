#pragma once
#include "GameObject.h"

class TextureData;

class UIButton : public GameObject
{
public:
	UIButton(TextureData *pIdleTexture, TextureData *pMouseOverTexture, TextureData *pMouseClicktexture, TextureData *pSelectedTexture);
	UIButton();
	virtual ~UIButton();

	void Select();
	void Unselect();

	bool IsMouseOver();
	bool IsClicked();

	void SetClickBoxSize(const Vector2 &size);

protected:
	virtual void OnMouseOver();
	virtual void OnMouseLeave();
	virtual void OnMouseClick();

private:
	virtual void Initialize(const GameContext &gameContext) override;
	virtual void Update(const GameContext &gameContext) override;
	virtual void Draw(const GameContext &gameContext) override;

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
	bool m_Selected;

private:
	TextureData *m_pIdleTexture = nullptr;
	TextureData *m_pMouseOverTexture = nullptr;
	TextureData *m_pClickTexture = nullptr;
	TextureData *m_pSelectedTexture = nullptr;

	TextureData *m_pCurrentTexture = nullptr;
	Vector2 m_Size;
};

