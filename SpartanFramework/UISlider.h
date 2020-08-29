#pragma once
#include "UIObject.h"
#include "ImageRenderComponent.h"
#include "Gradient.h"
#include "UISliderMaterial.h"

namespace Spartan
{
	namespace UI
	{
		class UISlider : public UIObject
		{
		public:
			UISlider();
			~UISlider();

			BASIC_OBJECT(UISlider, GameObject);

			void SetFillColor(const Color& color);
			void SetFillGradient(Gradient* pGradient);

			void SetProgress(float progress);
			Color GetColor();

			ImageRenderComponent* GetBackgroundImage();
			ImageRenderComponent* GetFillMaskImage();

		private:
			void Initialize(const Spartan::GameContext& gameContext) override;
			void Update(const Spartan::GameContext& gameContext) override;
			void Draw(const Spartan::GameContext& gameContext) override;
			void CreateMaterial();

		private:
			ImageRenderComponent* m_pBackgroundImage;
			ImageRenderComponent* m_pFillImage;
			Color m_FixedFillColor;
			Gradient* m_pFillColorGradient;
			float m_Progress;
			size_t m_GradientLayer;

		private:
			static size_t m_SliderMaterialID;
			static UISliderMaterial* m_pSliderMaterial;
		};
	}
}