#include "stdafx.h"
#include "Gradient.h"
#include "ContentManager.h"

Gradient::Gradient(size_t resolution) : m_Resolution(resolution), m_pTexture(nullptr)
{
	CreateDefaultKeys();
}

Gradient::~Gradient()
{
	if (m_pTexture != nullptr) delete m_pTexture;
	m_pTexture = nullptr;
}

void Gradient::BuildTexture()
{
	float* pData = GenerateGradientData();
	CreateTextureData(pData);
}

TextureData* Gradient::GetTexture() const
{
	return m_pTexture;
}

void Gradient::SetKey(const Math::Color& color, float percentage)
{
	auto it = std::find_if(m_GradientKeys.begin(), m_GradientKeys.end(), [&](const GradientKey& key)
	{
		return (key.Percentage == percentage);
	});

	if (it != m_GradientKeys.end())
	{
		GradientKey& key = *it;
		key.Color = color;
		return;
	}

	m_GradientKeys.push_back(GradientKey(color, percentage));
}

void Gradient::RemoveKey(float percentage)
{
	// We can't move or remove the start and end colors!
	if (percentage == 0.0f || percentage == 100.0f) return;

	auto it = std::find_if(m_GradientKeys.begin(), m_GradientKeys.end(), [&](const GradientKey& key)
	{
		return (key.Percentage == percentage);
	});

	if (it == m_GradientKeys.end()) return;

	m_GradientKeys.erase(it);
}

void Gradient::MoveKey(float fromPercentage, float toPercentage)
{
	// We can't move or remove the start and end colors!
	if (fromPercentage == 0.0f || fromPercentage == 100.0f) return;
	if (toPercentage == 0.0f || toPercentage == 100.0f) return;

	auto it = std::find_if(m_GradientKeys.begin(), m_GradientKeys.end(), [&](const GradientKey& key)
	{
		return (key.Percentage == fromPercentage);
	});

	if (it == m_GradientKeys.end()) return;

	RemoveKey(toPercentage);

	GradientKey& key = *it;
	key.Percentage = toPercentage;
}

void Gradient::ClearKeys()
{
	m_GradientKeys.clear();
	CreateDefaultKeys();
}

float* Gradient::GenerateGradientData()
{
	std::sort(m_GradientKeys.begin(), m_GradientKeys.end(), [](const GradientKey& key1, const GradientKey& key2)
	{
		return key1.Percentage < key2.Percentage;
	});

	Color* pPixles = new Color[m_Resolution];
	for (size_t i = 0; i < m_Resolution; i++)
	{
		float percentage = (i / (float)m_Resolution) * 100.0f;
		Color color = GetColor(percentage);
		pPixles[i] = color;
	}

	return (float*)pPixles;
}

void Gradient::CreateTextureData(float* pData)
{
	if (m_pTexture != nullptr) delete m_pTexture;
	m_pTexture = new TextureData("", Vector2::Zero());
	m_pTexture->BuildTextureFromData(Vector2((float)m_Resolution, 1.0f), pData, GL_RGBA, GL_RGBA);
	delete[] pData;
}

void Gradient::CreateDefaultKeys()
{
	SetKey(Color::Black(), 0.0f);
	SetKey(Color::White(), 100.0f);
}

Color Gradient::GetColor(float percentage)
{
	percentage = Math::Clamp(0.0f, 100.0f, percentage);

	if (percentage == 0.0f) return m_GradientKeys[0].Color;
	if (percentage == 100.0f) return m_GradientKeys[m_GradientKeys.size() - 1].Color;

	auto it = std::find_if(m_GradientKeys.begin(), m_GradientKeys.end(), [&](const GradientKey& key)
	{
		return percentage <= key.Percentage;
	});

	if (it == m_GradientKeys.begin()) return m_GradientKeys[0].Color;

	GradientKey& key2 = *it;
	if (key2.Percentage == 100.0f) return key2.Color;

	auto it2 = --it;
	GradientKey& key1 = *it;

	float percentageInRange = Math::InverseLerp(key1.Percentage, key2.Percentage, percentage);
	return Color::Lerp(key1.Color, key2.Color, percentageInRange);
}
