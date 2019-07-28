#include "stdafx.h"
#include "GameApp.h"
#include <ContentManager.h>
#include <SceneManager.h>
#include "LevelEditor.h"
#include <ApplicationStructs.h>
#include <InputManager.h>
#include <SoundManager.h>
#include <Framework.h>
#include "ComponentParameters.h"
#include "EditorWindow.h"
#include "BehaviorTreeEditor.h"

#define BEGIN_BUILDPARAMS_FUNCTION(x) template <typename T> \
inline void x(ComponentParameters<T> *pParam)

BEGIN_BUILDPARAMS_FUNCTION(Transform)
{
	auto pComp = dynamic_cast<TransformComponent*>(pParam->m_pComponent);

	auto pParam1 = new ComponentParam<Vector2>("Position", pComp->Position, pComp->Position);
	pParam->AddParam(pParam1);
	auto pParam2 = new ComponentParam<Vector3>("Rotation", pComp->Rotation, pComp->Rotation);
	pParam->AddParam(pParam2);
	auto pParam3 = new ComponentParam<Vector2>("Scale", pComp->Scale, pComp->Scale);
	pParam->AddParam(pParam3);
}

BEGIN_BUILDPARAMS_FUNCTION(Image)
{
	//auto pComp = dynamic_cast<ImageRenderComponent*>(pParam->m_pComponent);

	//auto pParam1 = new ComponentStringParam("File", pComp->m_AssetFile, pComp->m_AssetFile);
	//pParam->AddParam(pParam1);
}

GameTool::GameTool(const GameSettings &settings) : BaseGame(settings), m_Buffer("")
{
}

GameTool::~GameTool()
{
	ComponentParameterManager::Destroy();

	SDL_DestroyTexture(m_pRenderTexture);
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteTextures(1, &m_TextureID);
}

void GameTool::Initialize(const GameContext &gameContext)
{
	// Init GLEW
	glewInit();

	auto settings = BaseGame::GetGame()->GetGameSettings();
	/*m_pRenderTexture = SDL_CreateTexture(gameContext.pRenderer->GetSDLRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, settings.Window.Width, settings.Window.Height);
	if (!m_pRenderTexture)
		Utilities::Debug::Log("Error when creating a RenderTexture!", Utilities::LogLevel::Error);*/

	/*glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glGenFramebuffers(1, &m_FBO);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)settings.Window.Width, (GLsizei)settings.Window.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

	glGenRenderbuffers(1, &m_RenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, (GLsizei)settings.Window.Width, (GLsizei)settings.Window.Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

	glGenTextures(1, (GLuint*)&m_TextureID);
	glBindTexture(GL_TEXTURE_2D, (GLuint)m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)settings.Window.Width, (GLsizei)settings.Window.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (GLuint)m_FBO, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ComponentParameterManager::GetInstance()->Register(new ComponentParameters<TransformComponent>(Transform<TransformComponent>));
	ComponentParameterManager::GetInstance()->Register(new ComponentParameters<ImageRenderComponent>(Image<ImageRenderComponent>));

	SceneManager::GetInstance()->AddScene(new LevelEditor());

	UNREFERENCED_PARAMETER(gameContext);

	GLsizei w = (GLsizei)m_GameSettings.Window.Width;
	GLsizei h = (GLsizei)m_GameSettings.Window.Height;
	m_GameWindowWidth = w / 2.f;
	m_GameWindowHeight = h / 2.f;

	EditorWindow::GetWindow<BehaviorTreeEditor>();
}

void GameTool::GameUpdate(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void GameTool::GamePaint(const GameContext &gameContext)
{
	GLsizei w = (GLsizei)m_GameSettings.Window.Width;
	GLsizei h = (GLsizei)m_GameSettings.Window.Height;
	float aspect = (float)w / (float)h;

	// Draw scenes
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glViewport(0, 0, w, h);
	m_GameContext.pRenderer->ClearBackground();
	glEnable(GL_TEXTURE_2D);
	SceneManager::GetInstance()->Draw(m_GameContext);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//gameContext.pRenderer->RenderTexture(m_TextureID, w, h);

	ImGui::SetNextWindowSize(ImVec2(m_GameWindowWidth, m_GameWindowHeight), ImGuiSetCond_FirstUseEver);

	ImGui::Begin("Game Window");
	//glViewport(0, 0, m_GameSettings.Window.Width, m_GameSettings.Window.Height);
	//SceneManager::GetInstance()->Draw(m_GameContext);

	ImVec2 pos = ImGui::GetCursorScreenPos();
	float width = ImGui::GetWindowWidth();
	float height = width / aspect;
	ImGui::GetWindowDrawList()->AddImage(
		(void *)m_TextureID, ImVec2(pos.x,
			pos.y),
		ImVec2(pos.x + width, pos.y + height), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();

	ImGui::ShowDemoWindow();

	ContentManagerWindow();

	EditorWindows();

	/*ImGui::Begin("My Window");
	ImGui::Text("Hello, World! %d", 123);
	if (ImGui::Button("Save"))
	{
		// Do stuff
	}
	ImGui::InputText("string", m_Buffer, 10, IM_ARRAYSIZE(m_Buffer));
	ImGui::SliderFloat("float", &m_Slider, 0.0f, 1.0f);
	ImGui::End();*/


}

bool GameTool::RootInitialize()
{
	// Init GLEW
	glewInit();

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Utilities::Debug::LogError("SDL Could not initialize! SDL_Error: " + string(SDL_GetError()));

		return false;
	}

	// Use OpenGL 3.0
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Initialize GameContext
	m_GameContext.pRenderer = new Renderer();
	m_GameContext.pRenderer->Initialize(m_GameContext);
	m_GameContext.pTime = new GameTime();
	m_GameContext.pTime->Start();
	m_GameContext.pInput = new InputManager();
	m_GameContext.pSound = new SoundManager();
	m_GameContext.pSound->Initialize();
	m_GameContext.pParticleManager = new ParticleManager();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForOpenGL(m_GameContext.pRenderer->GetWindow(), m_GameContext.pRenderer->GetGLContext());
	ImGui_ImplOpenGL2_Init();

	io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("./EditorResources/ProggyClean.ttf", 16.f);
	//io.Fonts->AddFontFromFileTTF("./EditorResources/ProggyTiny.ttf", 12.f);
	//io.Fonts->AddFontFromFileTTF("./EditorResources/Karla-Regular.ttf", 16.f);
	io.Fonts->Build();

	ImGui::StyleColorsDark();

	// Initialize Content Manager
	ContentManager::GetInstance()->Initialize();

	// Initialize SDL_ttf
	if (TTF_Init() < 0)
	{
		Utilities::Debug::LogError("SDL_ttf Could not initialize! TTF_Error: " + string(TTF_GetError()));
		return false;
	}

	// Run user defined Initialize()
	Initialize(m_GameContext);

	// Initialise Scenes
	SceneManager::GetInstance()->Initialize(m_GameContext);

	return true;
}

bool GameTool::RootGameUpdate()
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

	// Tick ParticleManager
	m_GameContext.pParticleManager->Tick(m_GameContext);

	// Inside SDL events
	SDL_Event windowEvent;

	if (SDL_PollEvent(&windowEvent))
	{
		ImGui_ImplSDL2_ProcessEvent(&windowEvent);

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

void GameTool::RootGamePaint()
{
	// Clear the background
	m_GameContext.pRenderer->ClearBackground();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_GameContext.pRenderer->GetWindow());
	ImGui::NewFrame();

	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

	// Run user defined GamePaint()
	GamePaint(m_GameContext);

	reinterpret_cast<LevelEditor*>(SceneManager::GetInstance()->GetCurrentScene())->RenderGUI();

	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	// Paint Particles
	m_GameContext.pParticleManager->Paint(m_GameContext);

	// Update window
	SDL_GL_SwapWindow(m_GameContext.pRenderer->m_pWindow);

	// End the frame timer
	m_GameContext.pTime->EndFrame();
}

void GameTool::ContentManagerWindow()
{
	ImGui::SetNextWindowSize(ImVec2((float)m_GameSettings.Window.Width, 300.f));
	ImGui::SetNextWindowPos(ImVec2(0.f, (float)m_GameSettings.Window.Height - 300.f));

	ImGui::Begin("Content Manager");

	ImGui::End();
}

void GameTool::EditorWindows()
{
	for (auto pWindow : EditorWindow::m_pActiveEditorWindows)
		pWindow->RenderGUI();
}
