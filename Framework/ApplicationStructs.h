#pragma once
class Renderer;
class Time;
class CameraComponent;
class InputManager;
class SoundManager;
class ParticleManager;

struct WindowSettings
{
	WindowSettings() {}
	int Width = 800;
	int Height = 600;
};

struct GameSettings
{
	WindowSettings Window;
	std::string AppName;
	bool EnableVSync = false;
};

struct GameContext
{
	Renderer *pRenderer = nullptr;
	Time *pTime = nullptr;
	InputManager *pInput = nullptr;
	SoundManager *pSound = nullptr;
	ParticleManager *pParticleManager = nullptr;
};