#pragma once

using namespace std;
using namespace chrono;

using frame = duration<int32_t, ratio<1, 60>>;
using ms = duration<float, milli>;

class Time
{
public:
	Time() {}

	const float *GetDeltaTime() { return &m_DeltaTime; }
	const float *GetTime() { return &m_Time; }
	const float *GetTimeScale() { return &m_TimeScale; }
	const float *GetFrameRate() { return &m_FrameRate; }
	const int *GetTotalFrames() { return &m_TotalFrames; }
	void SetTimeScale(float scale) { m_TimeScale = scale; }

private:
	friend class BaseGame;
	void Start();
	void StartFrame();
	void EndFrame();
	void Update();

private:
	float m_DeltaTime = 0.0f;
	float m_Time = 0.0f;
	float m_TimeScale = 1.0f;
	float m_FrameRate = 0.0f;
	int m_TotalFrames = 0;

private:
	std::chrono::time_point<std::chrono::steady_clock> m_LastFrameStart;
	std::chrono::time_point<std::chrono::steady_clock> m_AppStart;
};

