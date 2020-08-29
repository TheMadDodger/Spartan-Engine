#include "stdafx.h"
#include "TextureData.h"

namespace Spartan
{
	TextureData::TextureData(const GLuint& textureID, const Math::Vector2& dimensions) : Content(),
		m_Origin(dimensions / 2.0f), m_TextureID(textureID), m_Dimensions(dimensions) {}

	TextureData::TextureData() : Content(),
		m_Origin(), m_TextureID(0), m_Dimensions() {}

	TextureData::~TextureData()
	{
		glDeleteTextures(1, &m_TextureID);
		if (m_pImage) SDL_FreeSurface(m_pImage);
		m_pImage = NULL;
	}

	SDL_Surface* TextureData::GetImage() { return m_pImage; };
	SDL_Texture* TextureData::GetTexture() { return m_pTexture; };
	const Math::Vector2& TextureData::GetDimensions() { return m_Dimensions; }
	const GLuint& TextureData::GetID() { return m_TextureID; }
	const Math::Vector2& TextureData::GetOrigin() { return m_Origin; }
	void TextureData::SetOrigin(const Math::Vector2& origin) { m_Origin = origin; }

	const Math::Float4 TextureData::ToTextureCoordinates(TextureData* pTexture, const SDL_Rect& src)
	{
		Float4 result;
		auto dimensions = pTexture->GetDimensions();
		result.x = (float)src.x / dimensions.x;
		result.y = (float)src.y / dimensions.y;

		result.w = (float)src.w / dimensions.x;
		result.h = (float)src.h / dimensions.y;

		return result;
	}

	void TextureData::BuildTextureFromData(const Math::Vector2& dimensions, float* pData, GLint internalFormat, GLenum dataFormat)
	{
		m_Dimensions = dimensions;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		GLenum e = glGetError();
		if (e != GL_NO_ERROR)
		{
			std::cerr << "Texture::CreateFromSurface, error binding textures, Error id = " << e << '\n';
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, (GLsizei)m_Dimensions.x, (GLsizei)m_Dimensions.y, 0, dataFormat, GL_FLOAT, pData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void TextureData::BuildTexture()
	{
		GLenum pixelFormat{ GL_RGB };
		switch (m_pImage->format->BytesPerPixel)
		{
		case 3:
			if (m_pImage->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGB;
			}
			else
			{
				pixelFormat = GL_BGR;
			}
			break;
		case 4:
			if (m_pImage->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGBA;
			}
			else
			{
				pixelFormat = GL_BGRA;
			}
			break;
		default:
			std::cerr << "Texture::CreateFromSurface, unknow pixel format, BytesPerPixel: " << m_pImage->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";
			return;
		}

		m_Dimensions = Math::Vector2((float)m_pImage->w, (float)m_pImage->h);

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		GLenum e = glGetError();
		if (e != GL_NO_ERROR)
		{
			std::cerr << "Texture::CreateFromSurface, error binding textures, Error id = " << e << '\n';
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pImage->w, m_pImage->h, 0, pixelFormat, GL_UNSIGNED_BYTE, m_pImage->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}