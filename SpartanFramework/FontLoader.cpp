#include "stdafx.h"
#include "FontLoader.h"

FontLoader::FontLoader()
{
}

FontLoader::~FontLoader()
{
}

FontData *FontLoader::LoadContent(const std::string &file)
{
	auto filePath = file;
	int size = FindFontSize(filePath);
	TTF_Font *pFont = TTF_OpenFont(filePath.data(), size);
	if (!pFont)
	{
		Utilities::Debug::LogWarning("FontLoader::LoadContent > Could not open Font file, TTF Error: " + string(TTF_GetError()));
		return nullptr;
	}
	FontData *pData = new FontData(file);
	pData->m_pTTFFont = pFont;

	return pData;
}

int FontLoader::FindFontSize(std::string &file)
{
	size_t index = file.find(':');
	if (index == string::npos)
	{
		return 16; // Return default font size
	}

	auto sizeText = file.substr(index + 1);
	file = file.substr(0, index);

	int size = 16;
	try
	{
		size = stoi(sizeText);
	}
	catch (const std::exception&)
	{
		Utilities::Debug::LogWarning("FontLoader::FindFontSize > Could not find a size after the :\n");
		return 16; // return the default size
	}
	return size;
}
