#include "stdafx.h"
#include "GradientLoader.h"

namespace Spartan
{
	GradientLoader::GradientLoader()
	{
	}

	GradientLoader::~GradientLoader()
	{
	}

	Gradient* GradientLoader::LoadContent(const std::string& file)
	{
		if (file.find(".bin") != std::string::npos) return LoadBinary(file);
		return LoadText(file);
	}

	Gradient* GradientLoader::LoadBinary(const std::string& file)
	{
		return nullptr;
	}

	Gradient* GradientLoader::LoadText(const std::string& file)
	{
		std::ifstream gradientFile(file);
		if (!gradientFile.is_open()) return nullptr;

		std::string line = "";
		
		Gradient* pGradient = nullptr;

		try
		{
			// First line
			getline(gradientFile, line);
			size_t commaIndex = line.find(',');
			if (commaIndex == string::npos) return nullptr;
			std::string resValue = line.substr(0, commaIndex);
			std::string layersValue = line.substr(commaIndex + 1);

			// Resolution and layer count
			int resolution = stoi(resValue);
			int layers = stoi(layersValue);
			pGradient = new Gradient(resolution, layers, file);

			// Gradient Keys
			size_t layer = 0;
			while (!gradientFile.eof())
			{
				getline(gradientFile, line);

				if (line == "endlayer")
				{
					++layer;
					continue;
				}

				size_t firstCommaIndex = line.find(',');
				size_t secondCommaIndex = line.find(',', firstCommaIndex + 1);
				size_t thirdCommaIndex = line.find(',', secondCommaIndex + 1);
				size_t fourthCommaIndex = line.find(',', thirdCommaIndex + 1);

				if (firstCommaIndex == string::npos || secondCommaIndex == string::npos || thirdCommaIndex == string::npos) return nullptr;

				std::string percentValue = line.substr(0, firstCommaIndex);
				std::string redValue = line.substr(firstCommaIndex + 1, firstCommaIndex + secondCommaIndex + 1);
				std::string greenValue = line.substr(secondCommaIndex + 1, secondCommaIndex + thirdCommaIndex + 1);
				std::string blueValue = line.substr(thirdCommaIndex + 1, thirdCommaIndex + fourthCommaIndex + 1);
				std::string alphaValue = line.substr(fourthCommaIndex + 1);

				float percent = stof(percentValue);
				float red = stof(redValue);
				float green = stof(greenValue);
				float blue = stof(blueValue);
				float alpha = stof(alphaValue);

				pGradient->SetKey(Color(red, green, blue, alpha), percent, layer);
			}

			gradientFile.close();
			return pGradient;
		}
		catch (const std::exception&)
		{
			if (gradientFile.is_open()) gradientFile.close();
			if (pGradient) delete pGradient;
			return nullptr;
		}
	}
}