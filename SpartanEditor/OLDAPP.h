//#pragma once
//
//#include <BaseGame.h>
//
//class GameTool : public Spartan::BaseGame
//{
//public:
//	GameTool(const Spartan::GameSettings &settings);
//	~GameTool();
//
//	// User defined application methods
//	void Initialize(const Spartan::GameContext &gameContext) override;
//	void GameUpdate(const Spartan::GameContext &gameContext) override;
//	void GamePaint(const Spartan::GameContext &gameContext) override;
//
//	virtual bool RootInitialize() override;
//	virtual bool RootGameUpdate() override;
//	virtual void RootGamePaint() override;
//
//private:
//	void ContentManagerWindow();
//	void EditorWindows();
//
//private:
//	char m_Buffer[10];
//	float m_Slider = 0.f;
//
//	SDL_Texture *m_pRenderTexture = nullptr;
//
//	GLuint m_TextureID;
//	GLuint m_FBO;
//	GLuint m_RenderBuffer;
//
//	float m_GameWindowWidth = 1280.f;
//	float m_GameWindowHeight = 720.f;
//};
//
