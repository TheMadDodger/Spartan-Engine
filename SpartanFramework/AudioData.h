#pragma once
#include "Content.h"

namespace Spartan
{
	class AudioData : public Content
	{
	public:
		AudioData();
		virtual ~AudioData();

		BASIC_OBJECT(AudioData, Content);

		Mix_Music* GetMusic() const;
		Mix_Chunk* GetWAVChunck() const;
		void SetVolume(int volume);
		int GetVolume() const;
		bool IsMusic() const;

	private:
		friend class AudioFileLoader;
		bool m_IsMusic = false;
		Mix_Music* m_pMusic = nullptr;
		Mix_Chunk* m_pChunck = nullptr;
		int m_Volume = MIX_MAX_VOLUME;
	};
}
