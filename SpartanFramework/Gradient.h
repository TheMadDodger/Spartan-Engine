#pragma once
#include "SEObject.h"

class TextureData;

struct GradientKey
{
	GradientKey(const Math::Color& color, float percentage) : Color(color), Percentage(Math::Clamp<float>(0.0f, 100.0f, percentage)) {}

	Math::Color Color;
	float Percentage;
};

class Gradient : public SEObject
{
public:
	Gradient(size_t resolution);
	virtual ~Gradient();

	void BuildTexture();
	TextureData* GetTexture() const;

	void SetKey(const Math::Color& color, float percentage);
	void RemoveKey(float percentage);
	void MoveKey(float fromPercentage, float toPercentage);
	void ClearKeys();

	Color GetColor(float percentage);

private:
	float* GenerateGradientData();
	void CreateTextureData(float* pData);
	void CreateDefaultKeys();

private:
	size_t m_Resolution;
	TextureData* m_pTexture;
	std::vector<GradientKey> m_GradientKeys;
};

