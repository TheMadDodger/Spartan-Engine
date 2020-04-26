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

	enum FullscreenMode
	{
		Exclusive = SDL_WINDOW_FULLSCREEN,
		Borderless = SDL_WINDOW_FULLSCREEN_DESKTOP,
	};

	struct GameSettings
	{
		WindowSettings Window;
		std::string AppName;
		bool EnableVSync = false;
		bool Fullscreen = false;
		FullscreenMode FullscreenMode = FullscreenMode::Exclusive;
		bool ResizableWindow = false;
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