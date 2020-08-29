#include "stdafx.h"
#include "FontData.h"

namespace Spartan
{
	FontData::FontData() : Content() {}

	Spartan::FontData::~FontData()
	{
		TTF_CloseFont(m_pTTFFont);
		m_pTTFFont = nullptr;
	}

	TTF_Font* FontData::GetFontData() { return m_pTTFFont; }
	int FontData::GetSize() { return TTF_FontHeight(m_pTTFFont); }
}
