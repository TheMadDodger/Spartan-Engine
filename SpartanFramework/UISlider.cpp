#include "stdafx.h"
#include "UISlider.h"
#include "MaterialManager.h"

namespace Spartan
{
	namespace UI
	{
		UISliderMaterial* UISlider::m_pSliderMaterial = nullptr;
		size_t UISlider::m_SliderMaterialID = 0;

		UISlider::UISlider() : m_Progress(0.0f), m_GradientLayer(0), m_pBackgroundImage(nullptr), m_pFillImage(nullptr)
		{
			m_pBackgroundImage = CreateDefaultComponent<ImageRenderComponent>();
			m_pFillImage = CreateDefaultComponent<ImageRenderComponent>();
		}

		UISlider::~UISlider()
		{
			if (m_pFillColorGradient)
				delete m_pFillColorGradient;

			m_pFillColorGradient = nullptr;
		}

		void UISlider::SetFillColor(const Color& color)
		{
			if (m_pFillColorGradient)
				delete m_pFillColorGradient;

			m_FixedFillColor = color;
		}

		void UISlider::SetFillGradient(Gradient* pGradient)
		{
			if (m_pFillColorGradient)
				delete m_pFillColorGradient;

			m_pFillColorGradient = pGradient;
		}

		void UISlider::SetProgress(float progress)
		{
			if (progress == m_Progress) return;
			m_Progress = progress;
			SetDirty();
		}

		ImageRenderComponent* UISlider::GetBackgroundImage()
		{
			return m_pBackgroundImage;
		}

		ImageRenderComponent* UISlider::GetFillMaskImage()
		{
			return m_pFillImage;
		}

		void UISlider::Initialize(const Spartan::GameContext& gameContext)
		{
			CreateMaterial();
			m_pFillImage->SetCustomMaterial(m_pSliderMaterial);
		}

		void UISlider::Update(const Spartan::GameContext& gameContext)
		{
		}

		void UISlider::Draw(const Spartan::GameContext& gameContext)
		{
			m_pSliderMaterial->SetColor(GetColor());
			m_pSliderMaterial->SetProgress(m_Progress);
		}

		void UISlider::CreateMaterial()
		{
			if (m_pSliderMaterial) return;

			m_SliderMaterialID = MaterialManager::CreateMaterial<UISliderMaterial>("./Resources/Shaders/UISlider.fx");
			m_pSliderMaterial = MaterialManager::GetMaterial<UISliderMaterial>(m_SliderMaterialID);
		}

		Color UISlider::GetColor()
		{
			return m_pFillColorGradient ? m_pFillColorGradient->GetColor(m_Progress, m_GradientLayer) : m_FixedFillColor;
		}
	}
}