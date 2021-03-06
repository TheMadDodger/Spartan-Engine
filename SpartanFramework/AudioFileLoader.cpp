#include "stdafx.h"
#include "AudioFileLoader.h"

using namespace std;

namespace SpartanEngine
{
	AudioFileLoader::AudioFileLoader()
	{
	}

	AudioFileLoader::~AudioFileLoader()
	{
	}

	AudioData* AudioFileLoader::LoadContent(const std::string& file)
	{
		AudioData* pAudioData = nullptr;
		if (file.find(".wav") != string::npos) // Load in as chunck
		{
			Mix_Chunk* pChunck = Mix_LoadWAV(file.data());
			if (pChunck == nullptr)
			{
				Utilities::Debug::LogError("AudioFileLoader::LoadContent > Could not load: " + file + "\nMix_Error: " + Mix_GetError());
				return nullptr;
			}
			pAudioData = new AudioData(file);
			pAudioData->m_pChunck = pChunck;
			pAudioData->m_IsMusic = false;
		}
		else // Load in as music
		{
			Mix_Music* pMusic = Mix_LoadMUS(file.data());
			if (pMusic == nullptr)
			{
				Utilities::Debug::LogError("AudioFileLoader::LoadContent > Could not load: " + file + "\nMix_Error: " + Mix_GetError());
				return nullptr;
			}
			pAudioData = new AudioData(file);
			pAudioData->m_pMusic = pMusic;
			pAudioData->m_IsMusic = true;
		}

		return pAudioData;
	}
}