#pragma once
#include "BaseComponent.h"

namespace SpartanEngine
{
	class AudioData;

	enum DecayType
	{
		Linear,
		Exponential,
		Logarithmic,
	};

	struct AudioSourceSettings
	{
		AudioSourceSettings(float minDecayDistance, float maxDecayDistance,
			DecayType decayType = DecayType::Exponential, float maxVolume = MIX_MAX_VOLUME) :
			MinDecayDistance(minDecayDistance), MaxDecayDistance(maxDecayDistance), MaxVolume(maxVolume), DistanceDecayType(decayType) {}

		//AudioSourceSettings(float minDecayDistance, float maxDecayDistance, float linearDecayStep, float maxVolume = MIX_MAX_VOLUME) :
			//MinDecayDistance(minDecayDistance), MaxDecayDistance(maxDecayDistance), LinearDecayStep(linearDecayStep), MaxVolume(maxVolume), DistanceDecayType(DecayType::Linear) {}

		AudioSourceSettings() {};

		float MinDecayDistance;
		float MaxDecayDistance;
		int Exponent = 2;
		//float LinearDecayStep;
		float MaxVolume = MIX_MAX_VOLUME;
		float MinVolume = 0.0f;

		bool IsConstant = false;

		DecayType DistanceDecayType = DecayType::Exponential;
	};

	class AudioSourceComponent : public BaseComponent
	{
	public:
		AudioSourceComponent();
		~AudioSourceComponent();

		void SetSettings(const AudioSourceSettings& settings);
		AudioSourceSettings& GetSettings();

		void Play(const GameContext& gameContext);

		AudioSourceSettings m_Settings;

	protected:
		void Initialize(const GameContext& gameContext) override;
		void Update(const GameContext& gameContext) override;

	private:
		float InterpolateVolume(Vector3& listenPosition);
		float LinInterpolate(float value);
		float ExpInterpolate(float value);
		float LogInterpolate(float value);

		void ConstantSource(const GameContext& gameContext);

		COMPONENT_EDITOR(AudioSourceComponent)

	private:
		const char* m_AudioFile;
		AudioData* m_pAudioData;

		bool m_bIsPlaying = false;
		int m_PlayingChannel = -1;
	};
}