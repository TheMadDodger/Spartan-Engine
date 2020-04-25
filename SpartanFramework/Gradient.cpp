#include "stdafx.h"
#include "Gradient.h"
#include "ContentManager.h"

namespace SpartanEngine
{
	Gradient::Gradient(size_t resolution, size_t layers) : m_Resolution(resolution), m_pTexture(nullptr), m_Layers(layers)
	{
		m_GradientKeys.resize(layers);
		CreateDefaultKeys();
	}

	Gradient::~Gradient()
	{
		if (m_pTexture != nullptr) delete m_pTexture;
		m_pTexture = nullptr;

		for (size_t i = 0; i < m_GradientKeys.size(); i++)
		{
			m_GradientKeys[i].clear();
		}
		m_GradientKeys.clear();
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

	void Gradient::SetKey(const Math::Color& color, float percentage, size_t layer)
	{
		std::vector<GradientKey>& keys = m_GradientKeys[layer];

		auto it = std::find_if(keys.begin(), keys.end(), [&](const GradientKey& key)
		{
			return (key.Percentage == percentage);
		});

		if (it != keys.end())
		{
			GradientKey& key = *it;
			key.Color = color;
			return;
		}

		keys.push_back(GradientKey(color, percentage));
	}

	void Gradient::RemoveKey(float percentage, size_t layer)
	{
		// We can't move or remove the start and end colors!
		if (percentage == 0.0f || percentage == 100.0f) return;

		std::vector<GradientKey>& keys = m_GradientKeys[layer];

		auto it = std::find_if(keys.begin(), keys.end(), [&](const GradientKey& key)
		{
			return (key.Percentage == percentage);
		});

		if (it == keys.end()) return;

		keys.erase(it);
	}

	void Gradient::MoveKey(float fromPercentage, float toPercentage, size_t layer)
	{
		// We can't move or remove the start and end colors!
		if (fromPercentage == 0.0f || fromPercentage == 100.0f) return;
		if (toPercentage == 0.0f || toPercentage == 100.0f) return;

		std::vector<GradientKey>& keys = m_GradientKeys[layer];

		auto it = std::find_if(keys.begin(), keys.end(), [&](const GradientKey& key)
		{
			return (key.Percentage == fromPercentage);
		});

		if (it == keys.end()) return;

		RemoveKey(toPercentage);

		GradientKey& key = *it;
		key.Percentage = toPercentage;
	}

	void Gradient::ClearKeys()
	{
		for (size_t i = 0; i < m_GradientKeys.size(); i++)
		{
			m_GradientKeys[i].clear();
		}
		m_GradientKeys.clear();
		CreateDefaultKeys();
	}

	float* Gradient::GenerateGradientData()
	{
		Color* pPixles = new Color[m_Resolution * m_Layers];
		for (size_t layer = 0; layer < m_Layers; layer++)
		{
			std::sort(m_GradientKeys[layer].begin(), m_GradientKeys[layer].end(), [](const GradientKey& key1, const GradientKey& key2)
			{
				return key1.Percentage < key2.Percentage;
			});

			for (size_t i = 0; i < m_Resolution; i++)
			{
				float percentage = (i / (float)m_Resolution) * 100.0f;
				Color color = GetColor(percentage, layer);
				pPixles[i + layer * m_Resolution] = color;
			}
		}

		return (float*)pPixles;
	}

	void Gradient::CreateTextureData(float* pData)
	{
		if (m_pTexture != nullptr) delete m_pTexture;
		m_pTexture = new TextureData("", Vector2::Zero());
		m_pTexture->BuildTextureFromData(Vector2((float)m_Resolution, (float)m_Layers), pData, GL_RGBA, GL_RGBA);
		delete[] pData;
	}

	void Gradient::CreateDefaultKeys()
	{
		for (size_t i = 0; i < m_Layers; i++)
		{
			SetKey(Color::Black(), 0.0f, i);
			SetKey(Color::White(), 100.0f, i);
		}
	}

	Color Gradient::GetColor(float percentage, size_t layer)
	{
		percentage = Math::Clamp(0.0f, 100.0f, percentage);

		std::vector<GradientKey>& keys = m_GradientKeys[layer];

		if (percentage == 0.0f) return keys[0].Color;
		if (percentage == 100.0f) return keys[keys.size() - 1].Color;

		auto it = std::find_if(keys.begin(), keys.end(), [&](const GradientKey& key)
		{
			return percentage <= key.Percentage;
		});

		if (it == keys.begin()) return keys[0].Color;

		GradientKey& key2 = *it;
		if (key2.Percentage == 100.0f) return key2.Color;

		auto it2 = --it;
		GradientKey& key1 = *it;

		float percentageInRange = Math::InverseLerp(key1.Percentage, key2.Percentage, percentage);
		return Color::Lerp(key1.Color, key2.Color, percentageInRange);
	}
}