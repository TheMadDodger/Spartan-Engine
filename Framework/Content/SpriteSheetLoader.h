#pragma once
#include "ContentLoader.h"
#include "ContentManager.h"

enum SpriteSheetBlockID : BYTE
{
	SEnd = 0,
	SGeneral = 1,
	SAnimationClips = 2,
	SFrames = 3,
};

class SpriteSheetLoader : public ContentLoader<SpriteSheetData>
{
public:
	SpriteSheetLoader();
	~SpriteSheetLoader();

	SpriteSheetData *LoadContent(const std::string& file) override;
};

