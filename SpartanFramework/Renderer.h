#pragma once

#include "MathHelpers.h"
#include "SkinnedQuad.h"

class TextureData;
class SpriteSheetData;
class FontData;
class Skeleton;

using namespace Math;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(const GameContext &gameContext);
	void DrawImage(TextureData *pImage, const GameContext &gameContext);
	void RenderTexture(TextureData *pBitmap);
	void RenderTexture(GLuint texID, float width, float height);
	void RenderSprite(TextureData *pBitmap, const SDL_Rect &src, const Vector2 &origin);
	void RenderText(FontData *pFont, const std::string &text, const SDL_Color &clr, const Origin &origin = Origin::Center, Uint32 maxWidth = 0);
	void ClearBackground();

	SDL_Renderer *GetSDLRenderer() { return m_pSDLRenderer; }
	SDL_Window *GetWindow() { return m_pWindow; }
	SDL_Surface *GetWindowSurface() { return m_pWindowSurface; }

	SDL_GLContext *GetGLContext() { return &m_pSDLContext; }

public:
	// Primitive Rendering
	void DrawSolidRect(const Vector2 &topLeft, const Vector2 &bottomRight, const Math::Color &color);
	void DrawSolidCircle(const Vector2 &center, float radius, const Math::Color &color);
	void DrawRect(const Vector2 &topLeft, const Vector2 &bottomRight, const Math::Color &color);
	void DrawQuadColorTexture(const Vector2 &topLeft, const Vector2 &bottomRight, const Math::Color &color, TextureData *pImage);
	void DrawCircle(const Vector2 &center, float radius, const Math::Color &color);
	void DrawLine(const Vector2 &start, const Vector2 &end, const Math::Color &color);
	void DrawPolygon(const std::vector<Vector2> &points, const Math::Color &color);
	void DrawSkinnedQuad(const std::vector<SkinnedVertice> &vertices, Skeleton *pSkeleton, TextureData *pTexture);

private:
	friend class BaseGame;
	friend class GameTool;
	SDL_Renderer * m_pSDLRenderer = nullptr;
	SDL_Window *m_pWindow = nullptr;
	SDL_Surface *m_pWindowSurface = nullptr;
	SDL_GLContext m_pSDLContext;

	const int CIRCLEPOLYGONS = 20;

private: // Internal private functions
	const Vector2 CalculateOrigin(const Math::Origin &origin, SDL_Surface *pImage);
};

