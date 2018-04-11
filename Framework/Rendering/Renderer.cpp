#include "stdafx.h"
#include "../../stdafx.h"
#include "Renderer.h"
#include "../BaseGame.h"
#include "../Content/ContentManager.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	SDL_FreeSurface(m_pWindowSurface);
	SDL_DestroyRenderer(m_pSDLRenderer);
	SDL_DestroyWindow(m_pWindow);
	m_pWindowSurface = nullptr;
	m_pSDLRenderer = nullptr;
	m_pWindow = nullptr;
}

void Renderer::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	// Open a window
	m_pWindow = SDL_CreateWindow(BaseGame::GetGame()->GetGameSettings().AppName.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		BaseGame::GetGame()->GetGameSettings().Window.Width, BaseGame::GetGame()->GetGameSettings().Window.Height, SDL_WINDOW_OPENGL);

	if (m_pWindow == NULL)
	{
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		//return false;
	}

	// Create OpenGL context 
	m_pSDLContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pSDLContext == nullptr)
	{
		std::cerr << "Could not ceate SDL GL Context: " << SDL_GetError() << std::endl;
		return;
	}

	if (BaseGame::GetGame()->GetGameSettings().EnableVSync)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			std::cerr << "Could not set SDL GL Swap interval: " << SDL_GetError() << std::endl;
			return;
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, BaseGame::GetGame()->GetGameSettings().Window.Width, 0, BaseGame::GetGame()->GetGameSettings().Window.Height); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, int(BaseGame::GetGame()->GetGameSettings().Window.Width), int(BaseGame::GetGame()->GetGameSettings().Window.Height));

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DrawImage(TextureData *pImage, const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	SDL_BlitSurface(pImage->GetImage(), NULL, m_pWindowSurface, NULL);
}

void Renderer::RenderSprite(TextureData *pBitmap, const SDL_Rect &src, const Vector2 &origin)
{
	float vertexLeft = 0;
	float vertexBottom = 0;
	float vertexRight = (float)src.w;
	float vertexTop = (float)src.h;

	auto texCoords = TextureData::ToTextureCoordinates(pBitmap, src);

	glBindTexture(GL_TEXTURE_2D, pBitmap->GetID());
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f((GLfloat)texCoords.x, (GLfloat)texCoords.y + (GLfloat)texCoords.h);
			glVertex2f((GLfloat)vertexLeft - origin.x, vertexBottom - origin.y);

			glTexCoord2f(texCoords.x, texCoords.y);
			glVertex2f(vertexLeft - origin.x, vertexTop - origin.y);

			glTexCoord2f(texCoords.x + texCoords.w, texCoords.y);
			glVertex2f(vertexRight - origin.x, vertexTop - origin.y);

			glTexCoord2f(texCoords.x + texCoords.w, texCoords.y + texCoords.h);
			glVertex2f(vertexRight - origin.x, vertexBottom - origin.y);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

void Renderer::RenderTexture(TextureData *pBitmap)
{
	float vertexLeft = 0;
	float vertexBottom = 0;
	float vertexRight = pBitmap->GetDimensions().x;
	float vertexTop = pBitmap->GetDimensions().y;

	glBindTexture(GL_TEXTURE_2D, pBitmap->GetID());
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(vertexLeft - pBitmap->GetOrigin().x, vertexBottom - pBitmap->GetOrigin().y);

			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(vertexLeft - pBitmap->GetOrigin().x, vertexTop - pBitmap->GetOrigin().y);

			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(vertexRight - pBitmap->GetOrigin().x, vertexTop - pBitmap->GetOrigin().y);

			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(vertexRight - pBitmap->GetOrigin().x, vertexBottom - pBitmap->GetOrigin().y);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

void Renderer::ClearBackground()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
