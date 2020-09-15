#include "stdafx.h"
#include "EditorApp.h"
#include <SceneManager.h>
#include "SceneWindow.h"
#include "GameWindow.h"
#include <InputManager.h>
#include <SceneManager.h>
#include <SoundManager.h>
#include <PhysicsProxy.h>
#include <PostProcessingStack.h>
#include "MenuBar.h"
#include "PopupManager.h"
#include <GameScene.h>
#include <GameObject.h>
#include "SceneViewCamera.h"
#include "EditorPreferencesWindow.h"
#include "SceneGraphWindow.h"
#include "InspectorWindow.h"
#include "Editor.h"
#include "GameObjectEditor.h"
#include "ComponentEditor.h"
#include "PropertyDrawer.h"
#include "StandardPropertyDrawers.h"
#include "ContentBrowser.h"

#include <LocalDatabase.h>
#include <AssetDatabase.h>
#include "Serializer.h"
#include "Tumbnail.h"
#include "TextureTumbnailGenerator.h"
#include "FontTumbnailGenerator.h"
#include "AudioTumbnailGenerator.h"

namespace Spartan
{
	EditorApp* EditorApp::m_pEditorApp = nullptr;

	EditorApp::EditorApp(BaseGame* pGame) : m_pGame(pGame), m_IsRunning(false), m_PlayModeActive(false), m_PlayModePaused(false), m_pComponentWindow(nullptr)
	{
		m_pEditorApp = this;
		BaseGame::m_AssetRootPath = "./../Assets";
	}

	EditorApp::~EditorApp()
	{
		delete m_pGame;
		m_pGame = nullptr;
		delete m_pComponentWindow;
		m_pComponentWindow = nullptr;
	}

	void EditorApp::Initialize()
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			Utilities::Debug::LogError("SDL Could not initialize! SDL_Error: " + string(SDL_GetError()));

			return;
		}

		// Use OpenGL 3.0
		const char* glsl_version = "#version 130";
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		// Create window with graphics context
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		// Initialize GameContext
		m_pGame->m_GameContext.pRenderer = new Renderer();
		m_pGame->m_GameContext.pRenderer->Initialize(m_pGame->m_GameContext);
		m_pGame->m_GameContext.pTime = new GameTime();
		m_pGame->m_GameContext.pTime->Start();
		m_pGame->m_GameContext.pInput = new InputManager();
		m_pGame->m_GameContext.pSound = new SoundManager();
		m_pGame->m_GameContext.pSound->Initialize();
		m_pGame->m_GameContext.pPhysicsProxy = new PhysicsProxy();
		m_pGame->m_GameContext.pPhysicsProxy->Initialize();
		//m_GameContext.pParticleManager = new ParticleManager();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForOpenGL(m_pGame->m_GameContext.pRenderer->GetWindow(), m_pGame->m_GameContext.pRenderer->GetGLContext());
		ImGui_ImplOpenGL3_Init(glsl_version);
		
		//io.Fonts->AddFontDefault();
		//io.Fonts->AddFontFromFileTTF("./EditorResources/ProggyClean.ttf", 16.f);
		//io.Fonts->AddFontFromFileTTF("./EditorResources/ProggyTiny.ttf", 12.f);
		//io.Fonts->AddFontFromFileTTF("./EditorResources/Karla-Regular.ttf", 16.f);
		//io.Fonts->Build();

		// Initialize Content Manager
		ContentManager::GetInstance()->Initialize();

		m_pGame->m_GameContext.pRenderer->CreateScreenAndMaterials();

		// Initialize SDL_ttf
		if (TTF_Init() < 0)
		{
			Utilities::Debug::LogError("SDL_ttf Could not initialize! TTF_Error: " + string(TTF_GetError()));
			return;
		}

		Serialization::Serializer::LoadSerializers();
		m_pGame->RegisterPrefabs(m_pGame->m_pPrefabs);
		m_pGame->RegisterCoreComponents();
		m_pGame->RegisterComponents();
		m_pGame->RegisterAssets();

		// Initialize PP
		PostProcessingStack::GetInstance();

		m_pGame->Initialize(m_pGame->m_GameContext);

		// Initialise Scenes
		SceneManager::GetInstance()->Initialize(m_pGame->m_GameContext);

		m_IsRunning = true;
		EditorApp::GetEditorApp()->InitializeGameObject(new Editor::SceneViewCamera());

		CreateDefaultMainMenuBar();
		RegisterPropDrawersInternal();
		m_pComponentWindow = new Editor::ComponentPopup();

		Editor::EditorWindow::GetWindow<Editor::SceneWindow>();
		Editor::EditorWindow::GetWindow<Editor::GameWindow>();

		Editor::Editor::RegisterEditor<Spartan::Editor::GameObjectEditor>();
		Editor::Editor::RegisterEditor<Spartan::Editor::ComponentEditor>();

		ImGui::GetStyle().WindowRounding = 4.389f;

		AssetDatabase::DiscoverAssets();

		Editor::Tumbnail::AddGenerator<Editor::TextureTumbnailGenerator>();
		Editor::Tumbnail::AddGenerator<Editor::FontTumbnailGenerator>();
		Editor::Tumbnail::AddGenerator<Editor::AudioTumbnailGenerator>();
	}

	void EditorApp::Tick()
	{
		// If a quit was called break out
		if (!m_IsRunning)
			return;

		// Start the timer
		m_pGame->m_GameContext.pTime->StartFrame();

		// Step the physicsworld
		if (m_PlayModeActive && !m_PlayModePaused) m_pGame->m_GameContext.pPhysicsProxy->Step(m_pGame->m_GameContext);

		// Update InputManager
		m_pGame->m_GameContext.pInput->Update();

		// Update audio
		m_pGame->m_GameContext.pSound->Update();

		// Tick ParticleManager
		//m_GameContext.pParticleManager->Tick(m_GameContext);

		// Inside SDL events
		SDL_Event windowEvent;

		if (SDL_PollEvent(&windowEvent))
		{
			ImGui_ImplSDL2_ProcessEvent(&windowEvent);

			switch (windowEvent.type)
			{
			case SDL_QUIT:
				m_IsRunning = false;
			case SDL_KEYUP:
				m_pGame->m_GameContext.pInput->KeyUp(&windowEvent.key);
				break;
			case SDL_KEYDOWN:
				m_pGame->m_GameContext.pInput->KeyDown(&windowEvent.key);
				break;
			case SDL_MOUSEMOTION:
				m_pGame->m_GameContext.pInput->HandleMouseMotionEvent(&windowEvent.motion, m_pGame->m_GameSettings.Window.Height);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_pGame->m_GameContext.pInput->MouseDown(&windowEvent.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_pGame->m_GameContext.pInput->MouseUp(&windowEvent.button);
				break;
			case SDL_MOUSEWHEEL:
				m_pGame->m_GameContext.pInput->HandleMouseScrollEvent(&windowEvent.wheel);
				break;
			case SDL_WINDOWEVENT:
				HandleWindowEvent(&windowEvent);
				break;
			default:
				break;
			}
		}

		// Update Scenes
		if (m_PlayModeActive)
		{
			if (!m_PlayModePaused) SceneManager::GetInstance()->Update(m_pGame->m_GameContext);
		}
		else EditorUpdateScene();

		// Update the timer
		m_pGame->m_GameContext.pTime->Update();

		// AutoLogger
		Utilities::Debug::UpdateAutoLogger(m_pGame->m_GameContext.pTime);
	}

	void EditorApp::Cleanup()
	{
		Editor::EditorWindow::Cleanup();
		Editor::SceneViewCamera::Destroy();
		Editor::Editor::Cleanup();
		Editor::PropertyDrawer::Cleanup();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void EditorApp::Run()
	{
		Initialize();

		//AssetDatabase::DiscoverAssets();

		std::ofstream fStream("testscene.scene");
		Spartan::SceneManager::GetInstance()->GetCurrentScene()->Serialize(fStream);
		fStream.close();

		while (m_IsRunning)
		{
			Tick();
			Paint();
		}
		Cleanup();
	}

	void EditorApp::InitializeGameObject(GameObject* pObject)
	{
		pObject->RootInitialize(m_pGame->m_GameContext);
	}

	void EditorApp::UpdateGameObject(GameObject* pObject)
	{
		pObject->RootUpdate(m_pGame->m_GameContext);
	}

	EditorApp* EditorApp::GetEditorApp()
	{
		return m_pEditorApp;
	}

	void EditorApp::RenderScene()
	{
		Spartan::SceneManager::GetInstance()->Draw(m_pGame->m_GameContext);
	}

	void EditorApp::EnterPlayMode()
	{
		if (m_PlayModeActive) return;

		// TODO: Save scene

		m_PlayModeActive = true;
	}

	void EditorApp::ExitPlayMode()
	{
		if (!m_PlayModeActive) return;

		m_PlayModeActive = false;

		// TODO: Reload scene

	}

	void EditorApp::EditorUpdateScene()
	{
		GameScene* pScene = SceneManager::GetInstance()->GetCurrentScene();
		for (size_t i = 0; i < pScene->GetChildCount(); i++)
		{
			GameObject* pRootChild = pScene->GetChild(i);
			if (pRootChild->m_Enabled) EditorUpdateObject(pRootChild);
		}
	}

	void EditorApp::EditorUpdateObject(GameObject* pObject)
	{
		if (!pObject->m_bInitialized) // If we haven't initialised yet
		{
			// We initialize
			pObject->RootInitialize(m_pGame->m_GameContext);
		}

		pObject->BeginUpdate(m_pGame->m_GameContext);

		for (size_t i = 0; i < pObject->m_pComponents.size(); ++i)
		{
			auto pComponent = pObject->m_pComponents[i];
			if (pComponent->m_bEnabled && pComponent->m_CanTickInEditor) pComponent->RootUpdate(m_pGame->m_GameContext);
		}

		for (size_t i = 0; i < pObject->m_pChildren.size(); ++i)
		{
			auto pChild = pObject->m_pChildren[i];
			if (pChild->IsEnabled()) EditorUpdateObject(pChild);
		}

		// User defined Update()
		pObject->Update(m_pGame->m_GameContext);
	}

	void EditorApp::RegisterPropDrawersInternal()
	{
		PROPERTY_DRAWER(Editor::FloatDrawer);
		PROPERTY_DRAWER(Editor::IntDrawer);
		PROPERTY_DRAWER(Editor::BoolDrawer);
		PROPERTY_DRAWER(Editor::DoubleDrawer);
		PROPERTY_DRAWER(Editor::Vector2Drawer);
		PROPERTY_DRAWER(Editor::Vector3Drawer);
		PROPERTY_DRAWER(Editor::Vector4Drawer);
		PROPERTY_DRAWER(Editor::ColorDrawer);
		PROPERTY_DRAWER(Editor::QuaternionDrawer);

		RegisterPropertyDrawers();
	}

	void EditorApp::Paint()
	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(m_pGame->m_GameContext.pRenderer->GetWindow());
		ImGui::NewFrame();

		m_pComponentWindow->OnGUI();
		Editor::MenuBar::OnGUI();
		Editor::PopupManager::OnGUI();

		bool open = true;
		//ImGui::ShowDemoWindow(&open);

		//{
		//	static float f = 0.0f;
		//	static int counter = 0;
		//
		//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
		//
		//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		//
		//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//
		//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//		counter++;
		//	ImGui::SameLine();
		//	ImGui::Text("counter = %d", counter);
		//
		//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//	ImGui::End();
		//}

		//// Draw editors
		Editor::EditorWindow::RenderWindows();

		ImGui::Render();
		Utilities::Debug::LogGLError(glGetError());

		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		Utilities::Debug::LogGLError(glGetError());
		RenderTexture::EndFinalRender();
		m_pGame->m_GameContext.pRenderer->ClearBackground();

		// Paint Particles
		//m_pGame->m_GameContext.pParticleManager->Paint(m_GameContext);

		// Update window
		SDL_GL_SwapWindow(m_pGame->m_GameContext.pRenderer->GetWindow());
		Utilities::Debug::LogGLError(glGetError());

		// End the frame timer
		m_pGame->m_GameContext.pTime->EndFrame();
	}

	void EditorApp::HandleWindowEvent(SDL_Event* event)
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
			//m_GameSettings.Window.Width = event->window.data1;
			//m_GameSettings.Window.Height = event->window.data2;
			//m_GameContext.pRenderer->HandleWindowResizing(m_GameSettings.Window.Width, m_GameSettings.Window.Height);
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

	void EditorApp::CreateDefaultMainMenuBar()
	{
		Editor::MenuBar::AddMenuItem("File/New/Scene", NULL);
		Editor::MenuBar::AddMenuItem("File/Preferences", []() {Editor::EditorWindow::GetWindow<Editor::EditorPreferencesWindow>();});
		Editor::MenuBar::AddMenuItem("Play/Start", [&]() {this->EnterPlayMode();});
		Editor::MenuBar::AddMenuItem("Play/Pauze", [&]() {m_PlayModePaused = !m_PlayModePaused;});
		Editor::MenuBar::AddMenuItem("Play/Stop", [&]() {this->ExitPlayMode();});

		Editor::MenuBar::AddMenuItem("File/Exit", [&]() {
			std::vector<std::string> buttons = { "Cancel", "Exit" };
			std::vector<std::function<void()>> buttonFuncs = { [&]() {Editor::PopupManager::CloseCurrentPopup();}, [&]() {m_IsRunning = false;} };
			Editor::PopupManager::OpenPopup("Exit", "Are you sure you want to exit? All unsaved changes will be lost!",
			buttons, buttonFuncs);});

		Editor::MenuBar::AddMenuItem("Window/Scene View", []() {Editor::EditorWindow::GetWindow<Editor::SceneWindow>(); });
		Editor::MenuBar::AddMenuItem("Window/Game View", []() {Editor::EditorWindow::GetWindow<Editor::GameWindow>(); });
		Editor::MenuBar::AddMenuItem("Window/Scene Graph", []() {Editor::EditorWindow::GetWindow<Editor::SceneGraphWindow>(); });
		Editor::MenuBar::AddMenuItem("Window/Inspector", []() {Editor::EditorWindow::GetWindow<Editor::InspectorWindow>(true); });
		Editor::MenuBar::AddMenuItem("Window/Content Browser", []() {Editor::EditorWindow::GetWindow<Editor::ContentBrowser>(); });
	}
}
