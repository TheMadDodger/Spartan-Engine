#pragma once
#include "ContentLoader.h"
#include "ContentManager.h"
#include "AudioData.h"

namespace Spartan
{
	class AudioFileLoader : public ContentLoader<AudioData>
	{
	public:
		AudioFileLoader();
		~AudioFileLoader();

	private:
		AudioData* LoadContent(const std::string& file) override;
	};
}