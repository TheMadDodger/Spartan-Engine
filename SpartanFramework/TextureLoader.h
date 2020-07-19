#pragma once
#include "ContentLoader.h"
#include "ContentManager.h"

namespace Spartan
{
	class TextureLoader : public ContentLoader<TextureData>
	{
	public:
		TextureLoader();
		~TextureLoader();

		TextureData* LoadContent(const std::string& file) override;
	};
}