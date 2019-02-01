#pragma once
#include "BaseComponent.h"
class TextRenderComponent : public BaseComponent
{
public:
	TextRenderComponent(const std::string &file);
	TextRenderComponent();
	virtual ~TextRenderComponent();

	void SetText(const std::string &text);
	void SetAllignment(const Origin &allignment);
	void SetColor(const Color &col);
	void SetFont(FontData *pFont);

	void SetMaxWidth(Uint32 maxWidth);

	COMPONENT_EDITOR(TextRenderComponent)

protected:
	void Initialize(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:

	std::string m_FontFile;
	std::string m_Text;
	FontData *m_pFont;
	Origin m_Origin;
	Color m_Color;
	bool m_FontSet = false;
	Uint32 m_MaxWidth = 0;
};

