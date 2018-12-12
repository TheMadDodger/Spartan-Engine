#include "stdafx.h"
#include "SpriteSheetLoader.h"
#include "BinaryContainer.h"

SpriteSheetLoader::SpriteSheetLoader()
{
}

SpriteSheetLoader::~SpriteSheetLoader()
{
}

SpriteSheetData *SpriteSheetLoader::LoadContent(const std::string& file)
{
	SpriteSheetData *pData = nullptr;

	if (!Utilities::BinaryContainer::OpenRead(file.data()))
	{
		Utilities::Debug::LogError("SpriteSheetLoader::LoadContent > Could not load: " + file);
		Utilities::BinaryContainer::Close();
		return nullptr;
	}

	int majorVersion = Utilities::BinaryContainer::Read<int>();
	int minorVersion = Utilities::BinaryContainer::Read<int>();

	if (majorVersion != 0)
	{
		Utilities::Debug::LogError("SpriteSheetLoader::LoadContent > Incompatible spritesheet file!" + file);
		Utilities::BinaryContainer::Close();
		return nullptr;
	}

	if (minorVersion != 1)
	{
		Utilities::Debug::LogWarning("SpriteSheetLoader::LoadContent > Minor versions don't match for this file!" + file);
	}

	pData = new SpriteSheetData(file);

	while (!Utilities::BinaryContainer::ReachedEndOfFile())
	{
		BYTE blockID = Utilities::BinaryContainer::Read<BYTE>();
		switch (blockID)
		{
		case SpriteSheetBlockID::SEnd:
			// Don't do anything
			break;

		case SpriteSheetBlockID::SGeneral:
		{
			pData->m_ImageFile = Utilities::BinaryContainer::ReadString();
			pData->m_TotalClips = Utilities::BinaryContainer::Read<int>();
			size_t index = file.rfind('/');
			string imagePath = file.substr(0, index) + '/' + pData->m_ImageFile;
			pData->m_pImageData = ContentManager::GetInstance()->Load<TextureData>(imagePath);

			if (pData->m_pImageData == nullptr)
			{
				Utilities::Debug::LogWarning("SpriteSheetLoader::LoadContent > Could not load " + pData->m_ImageFile + ". Please make sure this file is in the same folder as the spritesheet file!");
				delete pData;
				pData = nullptr;
				return nullptr;
			}

			break;
		}

		case SpriteSheetBlockID::SAnimationClips:
		{
			for (int i = 0; i < pData->m_TotalClips; ++i)
			{
				AnimationClip clip{};
				clip.ClipID = Utilities::BinaryContainer::Read<int>();
				clip.Name = Utilities::BinaryContainer::ReadString();
				clip.NumberOfFrames = Utilities::BinaryContainer::Read<int>();
				clip.FramesPerSecond = Utilities::BinaryContainer::Read<int>();
				pData->m_AnimationClips.push_back(clip);
			}
			break;
		}

		case SpriteSheetBlockID::SFrames:
		{
			int numFrames = Utilities::BinaryContainer::Read<int>();
			
			for (int i = 0; i < numFrames; ++i)
			{
				int clipID = Utilities::BinaryContainer::Read<int>();
				FrameData frameData;
				frameData.FrameRect = Utilities::BinaryContainer::Read<SDL_Rect>();
				pData->m_AnimationClips[clipID].Frames.push_back(frameData);
			}
			break;
		}

		default:
			break;
		}
	}

	Utilities::BinaryContainer::Close();

	return pData;
}