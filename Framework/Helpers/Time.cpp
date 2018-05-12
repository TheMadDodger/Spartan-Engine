#include "stdafx.h"
#include "../../stdafx.h"
#include "Time.h"

void Time::Start()
{
	m_DeltaTime = 0.0f;
	m_Time = 0.0f;
	m_UnscaledDeltaTime = 0.0f;
	m_UnscaledTime = 0.0f;
	m_TimeScale = 1.0f;
	m_FrameRate = 0.0f;
	m_TotalFrames = 0;

	m_AppStart = std::chrono::steady_clock::now();
}

void Time::StartFrame()
{
	time_point<std::chrono::steady_clock> fpsTimer(steady_clock::now());

	m_LastFrameStart = std::chrono::steady_clock::now();
}

void Time::EndFrame()
{
	auto endTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> frameDuration = endTime - m_LastFrameStart;
	m_DeltaTime = duration_cast<ms>(frameDuration).count() * m_TimeScale;
	m_UnscaledDeltaTime = duration_cast<ms>(frameDuration).count();
	m_FrameRate = round(1.0f / (m_UnscaledDeltaTime / 1000.0f));
	++m_TotalFrames;
}

void Time::Update()
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> appDuration = currentTime - m_AppStart;
	m_Time = appDuration.count() * m_TimeScale;
	m_UnscaledTime = appDuration.count();
}
