#include "stdafx.h"
#include "BaseGame.h"
#include "ContentManager.h"
#include "TextureLoader.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "MaterialManager.h"
#include "PhysicsProxy.h"

#ifdef _DEBUG
#include "ConsoleInput.h"
#endif // _DEBUG
#include "PostProcessingStack.h"
#include "Components.h"

namespace Spartan
{
	BaseGame* BaseGame::m_pGame = nullptr;

	BaseGame::BaseGame(const GameSettings& settings) : m_GameSettings(settings)
	{
		SetGame(this);
	}

	BaseGame::~BaseGame()
	{
		// Clean up content
		ContentManager::Destroy();

		// Clean up scenes
		SceneManager::Destroy();

		// Cleanup PP
		PostProcessingStack::Destroy();

		// Cleanup materials
		MaterialManager::Cleanup();

		// Clean up GameContext
		delete m_GameContext.pRenderer;
		m_GameContext.pRenderer = nullptr;
		delete m_GameContext.pTime;
		m_GameContext.pTime = nullptr;
		delete m_GameContext.pInput;
		m_GameContext.pInput = nullptr;
		delete m_GameContext.pSound;
		m_GameContext.pSound = nullptr;
		delete m_GameContext.pPhysicsProxy;
		m_GameContext.pPhysicsProxy = nullptr;
		//delete m_GameContext.pParticleManager;
		//m_GameContext.pParticleManager = nullptr;

#ifdef _DEBUG
		delete m_pConspole;
#endif

		// SDL Cleanup
		SDL_Quit();
	}


	bool BaseGame::RootInitialize()
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			Utilities::Debug::LogError("SDL Could not initialize! SDL_Error: " + string(SDL_GetError()));

			return false;
		}

		// Use OpenGL 4.6
		int result = SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		if (result < 0) Utilities::Debug::LogError(SDL_GetError());
		result = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		if (result < 0) Utilities::Debug::LogError(SDL_GetError());
		result = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		if (result < 0) Utilities::Debug::LogError(SDL_GetError());
		//result = SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		//if (result < 0) Utilities::Debug::LogError(SDL_GetError());

		// Initialize GameContext
		m_GameContext.pRenderer = new Renderer();
		m_GameContext.pRenderer->Initialize(m_GameContext);
		m_GameContext.pTime = new GameTime();
		m_GameContext.pTime->Start();
		m_GameContext.pInput = new InputManager();
		m_GameContext.pSound = new SoundManager();
		m_GameContext.pSound->Initialize();
		m_GameContext.pPhysicsProxy = new PhysicsProxy();
		m_GameContext.pPhysicsProxy->Initialize();
		//m_GameContext.pParticleManager = new ParticleManager();

		// Initialize Content Manager
		ContentManager::GetInstance()->Initialize();

		m_GameContext.pRenderer->CreateScreenAndMaterials();

		// Initialize SDL_ttf
		if (TTF_Init() < 0)
		{
			Utilities::Debug::LogError("SDL_ttf Could not initialize! TTF_Error: " + string(TTF_GetError()));
			return false;
		}

		RegisterPrefabs(m_pPrefabs);
		RegisterCoreComponents();
		RegisterComponents();
		RegisterAssets();

		// Run user defined Initialize()
		Initialize(m_GameContext);

		// Initialize PP
		PostProcessingStack::GetInstance();

		// Initialise Scenes
		SceneManager::GetInstance()->Initialize(m_GameContext);

#ifdef _DEBUG
		m_pConspole = new ConsoleInput();
		m_pConspole->Initialize();
		RegisterConsoleCommands(m_pConspole);

		GLint maxUniformSize, maxUniformLocations;
		glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUniformSize);
		glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &maxUniformLocations);
		Utilities::Debug::LogInfo("GL_MAX_UNIFORM_BLOCK_SIZE: " + to_string(maxUniformSize));
		Utilities::Debug::LogInfo("GL_MAX_UNIFORM_LOCATIONS: " + to_string(maxUniformLocations));
#endif // _DEBUG

		return true;
	}

	bool BaseGame::RootGameUpdate()
	{
		// If a quit was called break out
		if (m_bQuitGame)
			return false;

		// Start the timer
		m_GameContext.pTime->StartFrame();

		// Step the physicsworld
		m_GameContext.pPhysicsProxy->Step(m_GameContext);

#ifdef _DEBUG
		// Update console commands
		m_pConspole->Update();
#endif // _DEBUG

		// Update InputManager
		m_GameContext.pInput->Update();

		// Update audio
		m_GameContext.pSound->Update();

		// Tick ParticleManager
		//m_GameContext.pParticleManager->Tick(m_GameContext);

		// Inside SDL events
		SDL_Event windowEvent;

		if (SDL_PollEvent(&windowEvent))
		{
			OnSDLEvent(&windowEvent);

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
			case SDL_MOUSEMOTION:
				m_GameContext.pInput->HandleMouseMotionEvent(&windowEvent.motion, m_GameSettings.Window.Height);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_GameContext.pInput->MouseDown(&windowEvent.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_GameContext.pInput->MouseUp(&windowEvent.button);
				break;
			case SDL_MOUSEWHEEL:
				m_GameContext.pInput->HandleMouseScrollEvent(&windowEvent.wheel);
				break;
			case SDL_WINDOWEVENT:
				HandleWindowEvent(&windowEvent);
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

		// Paint Particles
		//m_GameContext.pParticleManager->Paint(m_GameContext);

		// Run user defined GamePaint()
		GamePaint(m_GameContext);

		// Update window
		SDL_GL_SwapWindow(m_GameContext.pRenderer->m_pWindow);

		// Render to the screen
		m_GameContext.pRenderer->RenderEnd();

		// End the frame timer
		m_GameContext.pTime->EndFrame();
	}

	void BaseGame::ApplySettings(const GameSettings& newSettings)
	{
		m_GameSettings = newSettings;
		m_GameContext.pRenderer->ChangeWindow();
	}

	void BaseGame::HandleWindowEvent(SDL_Event* event)
	{
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " shown");
            break;
        case SDL_WINDOWEVENT_HIDDEN:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " hidden");
            break;
        case SDL_WINDOWEVENT_EXPOSED:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " exposed");
            break;
        case SDL_WINDOWEVENT_MOVED:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " moved to " + to_string(event->window.data1) + "," + to_string(event->window.data2));
            break;
        case SDL_WINDOWEVENT_RESIZED:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " resized to " + to_string(event->window.data1) + "," + to_string(event->window.data2));
			m_GameSettings.Window.Width = event->window.data1;
			m_GameSettings.Window.Height = event->window.data2;
			m_GameContext.pRenderer->HandleWindowResizing(m_GameSettings.Window.Width, m_GameSettings.Window.Height);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " size changed to " + to_string(event->window.data1) + "," + to_string(event->window.data2));
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " minimized");
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " maximized");
            break;
        case SDL_WINDOWEVENT_RESTORED:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " restored");
            break;
        case SDL_WINDOWEVENT_ENTER:
			Spartan::Utilities::Debug::LogInfo("Mouse entered window " + to_string(event->window.windowID));
            break;
        case SDL_WINDOWEVENT_LEAVE:
			Spartan::Utilities::Debug::LogInfo("Mouse left window " + to_string(event->window.windowID));
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " gained keyboard focus");
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " lost keyboard focus");
            break;
        case SDL_WINDOWEVENT_CLOSE:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " closed");
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " is offered a focus");
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " has a special hit test");
            break;
#endif
        default:
			Spartan::Utilities::Debug::LogInfo("Window " + to_string(event->window.windowID) + " got unknown event " + to_string(event->window.event));
            break;
        }
    }

	void BaseGame::RegisterCoreComponents()
	{
		REGISTER_COMPONENT(TransformComponent);
		REGISTER_COMPONENT(ImageRenderComponent);
		REGISTER_COMPONENT(CameraComponent);
		REGISTER_COMPONENT(AudioSourceComponent);
		REGISTER_COMPONENT(SpriteSheetComponent);
		REGISTER_COMPONENT(RigidBody2DComponent);
		REGISTER_COMPONENT(Collider2DComponent);
		REGISTER_COMPONENT(TextRenderComponent);
		//COMPONENT(ParticleComponent);
		//COMPONENT(UIContainer);
		REGISTER_COMPONENT(SkinnedMeshComponent);
		REGISTER_COMPONENT(LineRenderComponent);
		REGISTER_COMPONENT(ShakeComponent);
		REGISTER_COMPONENT(MeshRenderComponent);
		REGISTER_COMPONENT(AIComponent);
		REGISTER_COMPONENT(GridComponent);
		REGISTER_COMPONENT(PhysicsObjectComponent);
	}
}