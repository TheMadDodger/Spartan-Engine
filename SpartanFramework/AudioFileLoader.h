#pragma once
#include "ContentLoader.h"
#include "ContentManager.h"

class AudioFileLoader : public ContentLoader<AudioData>
{
public:
	AudioFileLoader();
	~AudioFileLoader();

	AudioData *LoadContent(const std::string& file) override;
};

