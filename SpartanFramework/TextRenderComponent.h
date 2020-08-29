#pragma once
#include "UIComponent.h"

namespace Spartan
{
	class TextRenderComponent : public UIComponent
	{
	public:
		TextRenderComponent();
		virtual ~TextRenderComponent();

		void SetText(const std::string& text);
		void SetColor(const Color& col);
		void SetFont(FontData* pFont);
		FontData* GetFont();
		TextureData* GetTextureData();
		const std::string& GetText();
		const Color& GetColor() const;

		void SetMaxWidth(Uint32 maxWidth);

		std::string m_FontFile;

		COMPONENT(TextRenderComponent);

	protected:
		void Draw(const GameContext& gameContext) override;

	private:
		std::string m_Text;
		TextureData* m_pTextTexture = nullptr;
		FontData* m_pFont;
		Color m_Color;
		bool m_FontSet = false;
		Uint32 m_MaxWidth = 0;
		bool m_HasSetSize;
	};
}