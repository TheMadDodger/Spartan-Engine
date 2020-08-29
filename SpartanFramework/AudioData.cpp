#include "stdafx.h"
#include "AudioData.h"

namespace Spartan
{
	AudioData::AudioData() : Content() {}

	AudioData::~AudioData()
	{
		if (m_pChunck)
			Mix_FreeChunk(m_pChunck);

		if (m_pMusic)
			Mix_FreeMusic(m_pMusic);

		m_pChunck = nullptr;
		m_pMusic = nullptr;
	}

	Mix_Music* AudioData::GetMusic() const
	{
		if (!m_IsMusic)
		{
			std::cerr << "AudioData::GetMusic > Object does not contain music!" << std::endl;
			return nullptr;
		}
		return m_pMusic;
	}

	Mix_Chunk* AudioData::GetWAVChunck() const
	{
		if (m_IsMusic)
		{
			std::cerr << "AudioData::GetWAVChunck > Object contains music!" << std::endl;
			return nullptr;
		}
		return m_pChunck;
	}

	bool AudioData::IsMusic() const
	{
		return m_IsMusic;
	}

	void AudioData::SetVolume(int volume)
	{
		if (volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
		m_Volume = volume;
	}

	int AudioData::GetVolume() const
	{
		return m_Volume;
	}
}