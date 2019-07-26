#pragma once

#include <BaseGame.h>

class GameTool : public BaseGame
{
public:
	GameTool(const GameSettings &settings);
	~GameTool();

	// User defined application methods
	void Initialize(const GameContext &gameContext) override;
	void GameUpdate(const GameContext &gameContext) override;
	void GamePaint(const GameContext &gameContext) override;

	virtual bool RootInitialize() override;
	virtual bool RootGameUpdate() override;
	virtual void RootGamePaint() override;

private:
	void ContentManagerWindow();
	void EditorWindows();

private:
	char m_Buffer[10];
	float m_Slider = 0.f;

	SDL_Texture *m_pRenderTexture = nullptr;

	GLuint m_TextureID;
	GLuint m_FBO;
	GLuint m_RenderBuffer;

	float m_GameWindowWidth = 1280.f;
	float m_GameWindowHeight = 720.f;
};

