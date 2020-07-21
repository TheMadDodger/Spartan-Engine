#pragma once
#include "stdafx.h"
#include "SEObject.h"

using namespace std;

namespace Spartan
{
	using frame = chrono::duration<int32_t, ratio<1, 60>>;
	using ms = chrono::duration<float, milli>;

	class GameTime : SEObject
	{
	public:
		GameTime() {}

		const float GetDeltaTime() { return m_DeltaTime; }
		const float GetTime() { return m_Time; }
		const float GetUnscaledDeltaTime() { return m_UnscaledDeltaTime; }
		const float GetUnscaledTime() { return m_UnscaledTime; }
		const float GetTimeScale() { return m_TimeScale; }
		const float GetFrameRate() { return m_FrameRate; }
		const int GetTotalFrames() { return m_TotalFrames; }
		void SetTimeScale(float scale) { m_TimeScale = scale; }

	public: // Reference returns
		const float* GetDeltaTimeRef() { return &m_DeltaTime; }
		const float* GetTimeRef() { return &m_Time; }
		const float* GetUnscaledDeltaTimeRef() { return &m_UnscaledDeltaTime; }
		const float* GetUnscaledTimeRef() { return &m_UnscaledTime; }
		const float* GetTimeScaleRef() { return &m_TimeScale; }
		const float* GetFrameRateRef() { return &m_FrameRate; }
		const int* GetTotalFramesRef() { return &m_TotalFrames; }

	private:
		friend class BaseGame;
		friend class EditorApp;
		void Start();
		void StartFrame();
		void EndFrame();
		void Update();

	private:
		float m_DeltaTime = 0.0f;
		float m_Time = 0.0f;

		float m_UnscaledDeltaTime = 0.0f;
		float m_UnscaledTime = 0.0f;

		float m_TimeScale = 1.0f;
		float m_FrameRate = 0.0f;
		int m_TotalFrames = 0;

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_LastFrameStart;
		std::chrono::time_point<std::chrono::steady_clock> m_AppStart;
	};
}