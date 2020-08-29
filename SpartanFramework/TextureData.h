#pragma once
#include "Content.h"

namespace Spartan
{
	class TextureData : public Content
	{
	public:
		TextureData(const GLuint& textureID, const Math::Vector2& dimensions);
		TextureData();
		virtual ~TextureData();

		BASIC_OBJECT(TextureData, Content);

		SDL_Surface* GetImage();
		SDL_Texture* GetTexture();
		const Math::Vector2& GetDimensions();
		const GLuint& GetID();
		const Math::Vector2& GetOrigin();
		void SetOrigin(const Math::Vector2& origin);

		static const Math::Float4 ToTextureCoordinates(TextureData* pTexture, const SDL_Rect& src);
		void BuildTextureFromData(const Math::Vector2& dimensions, float* pData, GLint internalFormat, GLenum dataFormat);

	private:
		void BuildTexture();

	private:
		friend class TextureLoader;
		friend class Renderer;
		SDL_Surface* m_pImage;
		SDL_Texture* m_pTexture;
		GLuint m_TextureID;

		Math::Vector2 m_Dimensions;
		Math::Vector2 m_Origin;
	};
}