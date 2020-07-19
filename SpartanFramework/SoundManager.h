#pragma once

namespace Spartan
{
	class SoundManager : Manager
	{
	public:
		SoundManager();
		~SoundManager();

		void Initialize();
		void Update();

		int PlaySound(AudioData* pSound, int loop = 0);
		void StopSound(int channel);
		void StopAllSounds();
		int ChannelsAvailable();

	private:
		void CleanUp();

	private:
		vector<AudioData*> m_Channels;
	};
}