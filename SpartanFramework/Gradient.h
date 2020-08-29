#pragma once
#include "Content.h"
#include "TextureData.h"

namespace Spartan
{
	struct GradientKey
	{
		GradientKey(const Math::Color& color, float percentage) : Color(color), Percentage(Math::Clamp<float>(0.0f, 100.0f, percentage)) {}

		Math::Color Color;
		float Percentage;
	};

	class Gradient : public Content
	{
	public:
		Gradient(size_t resolution, size_t layers, const std::string &path);
		Gradient(size_t resolution = 512, size_t layers = 1);
		virtual ~Gradient();

		BASIC_OBJECT(Gradient, Content);

		void BuildTexture();
		TextureData* GetTexture() const;

		void SetKey(const Math::Color& color, float percentage, size_t layer = 0);
		void RemoveKey(float percentage, size_t layer = 1);
		void MoveKey(float fromPercentage, float toPercentage, size_t layer = 0);
		void ClearKeys();

		Color GetColor(float percentage, size_t layer = 0);

	private:
		float* GenerateGradientData();
		void CreateTextureData(float* pData);
		void CreateDefaultKeys();

	private:
		size_t m_Resolution;
		size_t m_Layers;
		TextureData* m_pTexture;
		std::vector<std::vector<GradientKey>> m_GradientKeys;
	};
}