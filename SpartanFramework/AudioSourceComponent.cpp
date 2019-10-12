#include "stdafx.h"
#include "AudioSourceComponent.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "GameScene.h"
#include "Components.h"
#include "SoundManager.h"

AudioSourceComponent::AudioSourceComponent() : m_AudioFile(""), m_pAudioData(nullptr), BaseComponent("Audio Source")
{
}

AudioSourceComponent::~AudioSourceComponent()
{
}

void AudioSourceComponent::SetSettings(const AudioSourceSettings &settings)
{
	m_Settings = settings;
}

AudioSourceSettings &AudioSourceComponent::GetSettings()
{
	return m_Settings;
}

void AudioSourceComponent::Play(const GameContext &gameContext)
{
	gameContext.pSound->PlaySound(m_pAudioData);
}

void AudioSourceComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	if (m_pAudioData == nullptr)
	{
		m_pAudioData = ContentManager::GetInstance()->Load<AudioData>(m_AudioFile);
	}
}

void AudioSourceComponent::Update(const GameContext &gameContext)
{
	// Update volume
	auto camPos = GetGameObject()->GetGameScene()->GetActiveCamera()->GetPosition();
	float volume = InterpolateVolume(camPos);
	m_pAudioData->SetVolume((int)volume);

	// For constant sources
	if (m_Settings.IsConstant)
		ConstantSource(gameContext);
}

float AudioSourceComponent::InterpolateVolume(Vector2 &listenPosition)
{
	auto sourcePosition = GetGameObject()->GetTransform()->GetWorldPosition();

	float distance = Math::Distance(listenPosition, sourcePosition);

	// If its closer than the minimum decay distance return max volume
	if (distance <= m_Settings.MinDecayDistance) return m_Settings.MaxVolume;

	// If its further than the maximum decay distance, than return 0
	if (distance >= m_Settings.MaxDecayDistance) return m_Settings.MinVolume;

	// If its between these 2 values interpolate the volume using the specified method
	switch (m_Settings.DistanceDecayType)
	{
	case Linear:
		return LinInterpolate(distance);
	case Exponential:
		return ExpInterpolate(distance);
	case Logarithmic:
		return LogInterpolate(distance);
	}

	return 0.0f;
}

float AudioSourceComponent::LinInterpolate(float value)
{
	float max = m_Settings.MaxDecayDistance - m_Settings.MinDecayDistance;
	float newValue = value - m_Settings.MinDecayDistance;

	float factor = 1.0f - (newValue / max);

	return factor * (m_Settings.MaxVolume - m_Settings.MinVolume) + m_Settings.MinVolume;
}

float AudioSourceComponent::ExpInterpolate(float value)
{
	float max = m_Settings.MaxDecayDistance - m_Settings.MinDecayDistance;
	float newValue = value - m_Settings.MinDecayDistance;

	float factor = 1.0f - pow(newValue / max, m_Settings.Exponent);

	return factor * (m_Settings.MaxVolume - m_Settings.MinVolume) + m_Settings.MinVolume;
}

float AudioSourceComponent::LogInterpolate(float value)
{
	UNREFERENCED_PARAMETER(value);
	return 0.0f;
}

void AudioSourceComponent::ConstantSource(const GameContext &gameContext)
{
	if (m_pAudioData->GetVolume() > 0.0f) // Only play the sound if its interpolated volume is higher than 0
	{
		if (!m_bIsPlaying)
		{
			m_PlayingChannel = gameContext.pSound->PlaySound(m_pAudioData, -1);
			m_bIsPlaying = true;
		}
	}
	else // Stop the sound if it is playing
	{
		if (m_PlayingChannel != -1 && m_bIsPlaying)
		{
			gameContext.pSound->StopSound(m_PlayingChannel);
			m_bIsPlaying = false;
			m_PlayingChannel = -1;
		}
	}
}
