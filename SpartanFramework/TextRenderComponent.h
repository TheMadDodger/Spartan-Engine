#pragma once
#include "BaseComponent.h"
class TextRenderComponent : public BaseComponent
{
public:
	TextRenderComponent();
	virtual ~TextRenderComponent();

	void SetText(const std::string &text);
	void SetAllignment(const Origin &allignment);
	void SetColor(const Color &col);
	void SetFont(FontData *pFont);
	FontData *GetFont();
	TextureData *GetTextureData();
	const std::string &GetText();
	const Color &GetColor() const;

	void SetMaxWidth(Uint32 maxWidth);

	std::string m_FontFile;

	COMPONENT_EDITOR(TextRenderComponent)

protected:
	void Initialize(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	std::string m_Text;
	bool m_IsDirty = true;
	TextureData *m_pTextTexture = nullptr;
	FontData *m_pFont;
	Origin m_Origin;
	Color m_Color;
	bool m_FontSet = false;
	Uint32 m_MaxWidth = 0;
};

