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
		BaseGame::GetGame()->GetGameSettings().Window.Width, BaseGame::GetGame()->GetGameSettings().Window.Height, BaseGame::GetGame()->GetGameSettings().Fullscreen ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_OPENGL);

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

void Renderer::RenderText(FontData *pFont, const std::string & text, const SDL_Color & clr, const Origin &origin, Uint32 maxWidth)
{
	if (text.size() <= 0) return; // If there is no text, no need to waste resources to render it

	SDL_Surface *pTextSurface = (maxWidth == 0) ? TTF_RenderUTF8_Blended(pFont->GetFontData(), text.data(), clr) :
		TTF_RenderUTF8_Blended_Wrapped(pFont->GetFontData(), text.data(), clr, maxWidth);
	if (!pTextSurface)
	{
		Utilities::Debug::LogWarning("Renderer::RenderText > Could not render text surface! TTF_Error: " + string(TTF_GetError()));
		return;
	}
	TextureData *pTextTexture = new TextureData("", CalculateOrigin(origin, pTextSurface));
	pTextTexture->m_pImage = pTextSurface;
	pTextTexture->BuildTexture();
	RenderTexture(pTextTexture);

	delete pTextTexture;
	pTextTexture = nullptr;
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

void Renderer::DrawSolidRect(const Vector2 &topLeft, const Vector2 &bottomRight, const Math::Color &color)
{
	glBegin(GL_QUADS);
	{
		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)topLeft.x, (GLfloat)bottomRight.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)topLeft.x, (GLfloat)topLeft.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)bottomRight.x, (GLfloat)topLeft.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)bottomRight.x, (GLfloat)bottomRight.y);
	}
	glEnd();
}

void Renderer::DrawSolidCircle(const Vector2 &center, float radius, const Math::Color &color)
{
	float degreeStep = 360.0f / (float)CIRCLEPOLYGONS;

	glBegin(GL_TRIANGLES);
	{
		for (int step = 0; step < CIRCLEPOLYGONS; ++step)
		{
			float angle1 = degreeStep * step;
			float angle2 = degreeStep * (step + 1);

			// Start with center vertex
			glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
			glVertex2f((GLfloat)center.x, (GLfloat)center.y);

			// Calculate the other 2 vertices
			auto v1 = Math::LengthDir(radius, angle1) + center;
			auto v2 = Math::LengthDir(radius, angle2) + center;

			// Add the 2 vertices to the triangle
			glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
			glVertex2f((GLfloat)v1.x, (GLfloat)v1.y);

			glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
			glVertex2f((GLfloat)v2.x, (GLfloat)v2.y);
		}
	}
	glEnd();
}

void Renderer::DrawRect(const Vector2 &topLeft, const Vector2 &bottomRight, const Math::Color &color)
{
	glBegin(GL_LINES);
	{
		// TopLeft to TopRight
		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)topLeft.x, (GLfloat)topLeft.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)bottomRight.x, (GLfloat)topLeft.y);

		// TopRight to BottomRight
		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)bottomRight.x, (GLfloat)topLeft.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)bottomRight.x, (GLfloat)bottomRight.y);

		// BottomRight to BottomLeft
		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)bottomRight.x, (GLfloat)bottomRight.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)topLeft.x, (GLfloat)bottomRight.y);

		// BottomLeft to TopLeft
		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)topLeft.x, (GLfloat)bottomRight.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)topLeft.x, (GLfloat)topLeft.y);
	}
	glEnd();
}

void Renderer::DrawQuadColorTexture(const Vector2 &topLeft, const Vector2 &bottomRight, const Math::Color &color, TextureData *pImage)
{
	if (pImage)
	{
		glBindTexture(GL_TEXTURE_2D, pImage->GetID());
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glEnable(GL_TEXTURE_2D);
	}

	glBegin(GL_QUADS);
	{
		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f((GLfloat)topLeft.x, (GLfloat)bottomRight.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f((GLfloat)topLeft.x, (GLfloat)topLeft.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f((GLfloat)bottomRight.x, (GLfloat)topLeft.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f((GLfloat)bottomRight.x, (GLfloat)bottomRight.y);
	}
	glEnd();

	if (pImage)
	{
		glDisable(GL_TEXTURE_2D);
	}
}

void Renderer::DrawCircle(const Vector2 &center, float radius, const Math::Color &color)
{
	float degreeStep = 360.0f / (float)CIRCLEPOLYGONS;

	glBegin(GL_LINES);
	{
		for (int step = 0; step < CIRCLEPOLYGONS; ++step)
		{
			float angle1 = degreeStep * step;
			float angle2 = degreeStep * (step + 1);

			// Calculate the 2 vertices of the line segment
			auto v1 = Math::LengthDir(radius, angle1) + center;
			auto v2 = Math::LengthDir(radius, angle2) + center;

			// Add the 2 vertices to the triangle
			glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
			glVertex2f((GLfloat)v1.x, (GLfloat)v1.y);

			glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
			glVertex2f((GLfloat)v2.x, (GLfloat)v2.y);
		}
	}
	glEnd();
}

void Renderer::DrawLine(const Vector2 & start, const Vector2 & end, const Math::Color & color)
{
	glBegin(GL_LINES);
	{
		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)start.x, (GLfloat)start.y);

		glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
		glVertex2f((GLfloat)end.x, (GLfloat)end.y);
	}
	glEnd();
}

void Renderer::DrawPolygon(const std::vector<Vector2> &points, const Math::Color &color)
{
	glBegin(GL_LINES);
	{
		for (size_t i = 0; i < points.size() - 1; ++i)
		{
			auto point1 = points[i];
			auto point2 = points[i + 1];
			glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
			glVertex2f((GLfloat)point1.x, (GLfloat)point1.y);
			glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
			glVertex2f((GLfloat)point2.x, (GLfloat)point2.y);
		}
	}
	glEnd();
}

const Vector2 Renderer::CalculateOrigin(const Math::Origin &origin, SDL_Surface *pImage)
{
	Vector2 calculatedOrigin;

	switch (origin)
	{
	case TopLeft:
		calculatedOrigin = Vector2::Zero();
		break;

	case TopMiddle:
		calculatedOrigin = Vector2::Zero();
		calculatedOrigin.x = (float)pImage->w / 2.0f;
		break;

	case TopRight:
		calculatedOrigin = Vector2::Zero();
		calculatedOrigin.x = (float)pImage->w;
		break;

	case LeftCenter:
		calculatedOrigin = Vector2::Zero();
		calculatedOrigin.x = 0;
		calculatedOrigin.y = (float)pImage->h / 2.0f;
		break;

	case Center:
		calculatedOrigin = Vector2::Zero();
		calculatedOrigin.x = (float)pImage->w / 2.0f;
		calculatedOrigin.y = (float)pImage->h / 2.0f;
		break;

	case RightCenter:
		calculatedOrigin = Vector2::Zero();
		calculatedOrigin.x = (float)pImage->w;
		calculatedOrigin.y = (float)pImage->h / 2.0f;
		break;

	case BottomLeft:
		calculatedOrigin = Vector2::Zero();
		calculatedOrigin.x = 0;
		calculatedOrigin.y = (float)pImage->h;
		break;

	case BottomMiddle:
		calculatedOrigin = Vector2::Zero();
		calculatedOrigin.x = (float)pImage->w / 2.0f;
		calculatedOrigin.y = (float)pImage->h;
		break;

	case BottomRight:
		calculatedOrigin = Vector2::Zero();
		calculatedOrigin.x = (float)pImage->w;
		calculatedOrigin.y = (float)pImage->h;
		break;

	default:
		break;
	}

	return calculatedOrigin;
}