#pragma once
#include "ContentManager.h"
#include "FontData.h"

namespace Spartan
{
	class FontLoader : public ContentLoader<FontData>
	{
	public:
		FontLoader();
		~FontLoader();

		FontData* LoadContent(const std::string& file) override;

	private:
		int FindFontSize(std::string& file);
	};
}