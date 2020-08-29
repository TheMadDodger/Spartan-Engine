#pragma once
#include "Content.h"

namespace Spartan
{
	class FontData : public Content
	{
	public:
		FontData();
		virtual ~FontData();

		BASIC_OBJECT(FontData, Content);

		TTF_Font* GetFontData();
		int GetSize();

	private:
		friend class FontLoader;
		TTF_Font* m_pTTFFont = nullptr;
	};
}