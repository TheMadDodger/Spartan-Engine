#pragma once

namespace SpartanEngine
{
	class Renderer;
	class GameTime;
	class CameraComponent;
	class InputManager;
	class SoundManager;
	//class ParticleManager;

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
		bool Fullscreen = false;
	};

	struct GameContext
	{
		Renderer* pRenderer = nullptr;
		GameTime* pTime = nullptr;
		InputManager* pInput = nullptr;
		SoundManager* pSound = nullptr;
		//ParticleManager *pParticleManager = nullptr;
	};
}