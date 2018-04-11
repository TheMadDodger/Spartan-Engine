#include "stdafx.h"
#include "../stdafx.h"
#include "BaseGame.h"
#include "Content/ContentManager.h"
#include "Content/TextureLoader.h"
#include "Scenes/SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"

BaseGame *BaseGame::m_pGame = nullptr;

BaseGame::BaseGame(const GameSettings &settings) : m_GameSettings(settings)
{
	SetGame(this);
}

BaseGame::~BaseGame()
{
	// Clean up content
	ContentManager::Destroy();

	// Clean up scenes
	SceneManager::Destroy();

	// Clean up GameContext
	delete m_GameContext.pRenderer;
	m_GameContext.pRenderer = nullptr;
	delete m_GameContext.pTime;
	m_GameContext.pTime = nullptr;
	delete m_GameContext.pInput;
	m_GameContext.pInput = nullptr;
	delete m_GameContext.pSound;
	m_GameContext.pSound = nullptr;

	// SDL Cleanup
	SDL_Quit();
}


bool BaseGame::RootInitialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL Could not initialise! SDL Error: " << SDL_GetError() << std::endl;

		return false;
	}

	// Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Initialize GameContext
	m_GameContext.pRenderer = new Renderer();
	m_GameContext.pRenderer->Initialize(m_GameContext);
	m_GameContext.pTime = new Time();
	m_GameContext.pTime->Start();
	m_GameContext.pInput = new InputManager();
	m_GameContext.pSound = new SoundManager();
	m_GameContext.pSound->Initialize();

	// Initialize Content Manager
	ContentManager::GetInstance()->Initialize();

	// Run user defined Initialize()
	Initialize(m_GameContext);

	// Initialise Scenes
	SceneManager::GetInstance()->Initialize(m_GameContext);

	return true;
}

bool BaseGame::RootGameUpdate()
{
	// If a quit was called break out
	if (m_bQuitGame)
		return false;

	// Start the timer
	m_GameContext.pTime->StartFrame();

	// Update InputManager
	m_GameContext.pInput->Update();

	// Update audio
	m_GameContext.pSound->Update();

	// Inside SDL events
	SDL_Event windowEvent;

	if (SDL_PollEvent(&windowEvent))
	{
		switch (windowEvent.type)
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYUP:
			m_GameContext.pInput->KeyUp(&windowEvent.key);
			break;
		case SDL_KEYDOWN:
			m_GameContext.pInput->KeyDown(&windowEvent.key);
			break;

		default:
			break;
		}
	}

	// Update Scenes
	SceneManager::GetInstance()->Update(m_GameContext);

	// Run user defined GameUpdate()
	GameUpdate(m_GameContext);

	// Update the timer
	m_GameContext.pTime->Update();

	// AutoLogger
	Utilities::Debug::UpdateAutoLogger(m_GameContext.pTime);

	return true;
}

void BaseGame::RootGamePaint()
{
	// Clear the background
	m_GameContext.pRenderer->ClearBackground();

	// Draw scenes
	SceneManager::GetInstance()->Draw(m_GameContext);

	// Run user defined GamePaint()
	GamePaint(m_GameContext);

	// Update window
	SDL_GL_SwapWindow(m_GameContext.pRenderer->m_pWindow);

	// End the frame timer
	m_GameContext.pTime->EndFrame();
}

