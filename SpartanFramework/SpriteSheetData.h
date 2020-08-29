#pragma once
#include "Content.h"

namespace Spartan
{
	struct FrameData
	{
		SDL_Rect FrameRect;
	};

	struct AnimationClip
	{
		std::string Name;
		int NumberOfFrames;
		int FramesPerSecond;
		int ClipID;
		std::vector<FrameData> Frames;
	};

	class SpriteSheetData : public Content
	{
	public:
		SpriteSheetData();
		virtual ~SpriteSheetData();

		BASIC_OBJECT(SpriteSheetData, Content);

	private:
		friend class SpriteSheetLoader;
		friend class SpriteSheetComponent;
		std::vector<AnimationClip> m_AnimationClips;
		int m_TotalClips;
		TextureData* m_pImageData;
	};
}

