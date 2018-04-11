#include "stdafx.h"
#include "../../stdafx.h"
#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

TextureData *TextureLoader::LoadContent(const std::string &file)
{
	SDL_Surface *pSDLImage = IMG_Load(file.data());

	if (pSDLImage == NULL)
	{
		std::cout << "SDL Could not load image " << file << " ! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	TextureData *pData = new TextureData(file, Vector2(pSDLImage->w / 2.0f, pSDLImage->h / 2.0f));
	pData->m_pImage = pSDLImage;
	pData->BuildTexture();

	return pData;
}
