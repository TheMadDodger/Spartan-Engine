#pragma once

#include "../Helpers/MathHelpers.h"

class TextureData;
class SpriteSheetData;

using namespace Math;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(const GameContext &gameContext);
	void DrawImage(TextureData *pImage, const GameContext &gameContext);
	void RenderTexture(TextureData *pBitmap);
	void RenderSprite(TextureData *pBitmap, const SDL_Rect &src, const Vector2 &origin);
	void ClearBackground();

	SDL_Renderer *GetSDLRenderer() { return m_pSDLRenderer; }
	SDL_Window *GetWindow() { return m_pWindow; }
	SDL_Surface *GetWindowSurface() { return m_pWindowSurface; }

public:
	// Primitive Rendering
	void DrawSolidRect(const Vector2 &topLeft, const Vector2 &bottomRight, const SDL_Color &color);
	void DrawSolidCircle(const Vector2 &center, float radius, const SDL_Color &color);
	void DrawRect(const Vector2 &topLeft, const Vector2 &bottomRight, const SDL_Color &color);
	void DrawCircle(const Vector2 &center, float radius, const SDL_Color &color);

private:
	friend class BaseGame;
	SDL_Renderer * m_pSDLRenderer = nullptr;
	SDL_Window *m_pWindow = nullptr;
	SDL_Surface *m_pWindowSurface = nullptr;
	SDL_GLContext m_pSDLContext;
};

