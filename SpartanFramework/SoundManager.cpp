#include "stdafx.h"
#include "SoundManager.h"
#include "ContentManager.h"

#define BUFFER 1024
#define W 640 /* NEVER make this be less than BUFFER! */
#define H 480
#define H2 (H/2)
#define H4 (H/4)
#define Y(sample) (((sample)*H)/4/0x7fff)

namespace SpartanEngine
{
	SoundManager::SoundManager()
	{
		m_Channels.resize(MIX_CHANNELS);
		for (size_t i = 0; i < m_Channels.size(); ++i)
		{
			m_Channels[i] = nullptr;
		}
	}

	SoundManager::~SoundManager()
	{
		CleanUp();
		m_Channels.clear();
	}

	void SoundManager::Initialize()
	{
		if (Mix_Init(-1) < 0) // Initialize Mixer
		{
			Utilities::Debug::LogError("SoundManager::Initialize > Could not initialize SDL_mixer!\nMixer Error: " + string(Mix_GetError()));
			return;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, BUFFER) < 0) // Open Audio Device
		{
			Utilities::Debug::LogError("SoundManager::Initialize > Could not open Audio Device!\nMixer Error: " + string(Mix_GetError()));
			return;
		}

		Mix_AllocateChannels(MIX_CHANNELS); // Allocate audio channels
	}

	void SoundManager::Update()
	{
		for (size_t i = 0; i < m_Channels.size(); ++i)
		{
			if (m_Channels[i])
			{
				Mix_Volume((int)i, m_Channels[i]->GetVolume());
				if (!Mix_Playing((int)i))
				{
					m_Channels[i] = nullptr;
				}
			}
		}
	}

	/*Returns the channel that was used*/
	int SoundManager::PlaySound(AudioData* pSound, int loop)
	{
		if (pSound->IsMusic()) // Play it as music
		{
			Mix_VolumeMusic(pSound->GetVolume());
			if (!Mix_PlayingMusic())
			{
				Mix_PlayMusic(pSound->GetMusic(), loop);
			}
			else
			{
				Mix_HaltMusic();
				Mix_PlayMusic(pSound->GetMusic(), loop);
			}
			return -1;
		}
		else
		{
			if (ChannelsAvailable() > 0)
			{
				int channel = Mix_PlayChannel(-1, pSound->GetWAVChunck(), loop);
				if (channel < 0)
				{
					Utilities::Debug::LogWarning("SoundManager::PlaySound > Could not play sound!\nMixer Error: " + string(Mix_GetError()));
					return -2;
				}
				Mix_Volume(channel, pSound->GetVolume());
				m_Channels[(size_t)channel] = pSound;
				return channel;
			}
		}
		return -2;
	}

	void SoundManager::StopSound(int channel)
	{
		Mix_HaltChannel(channel);
	}

	void SoundManager::StopAllSounds()
	{
		StopSound(-1);
	}

	int SoundManager::ChannelsAvailable()
	{
		int channels = 0;
		for_each(m_Channels.begin(), m_Channels.end(), [&channels](const AudioData* pAudio) { if (pAudio == nullptr) ++channels; });
		return channels;
	}

	void SoundManager::CleanUp()
	{
		Mix_CloseAudio();
		Mix_Quit();
	}
}