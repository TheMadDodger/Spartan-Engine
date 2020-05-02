#pragma once
#include "UIRenderMaterial.h"

namespace SpartanEngine
{
	namespace UI
	{
		class UISliderMaterial : public UIRenderMaterial
		{
		public:
			UISliderMaterial(ShaderData* pShader);
			~UISliderMaterial();

			void SetColor(const SpartanEngine::Color& color);
			void SetProgress(float progress);

		private:
			void SetShaderVars(BaseComponent* pComponent) override;

		private:
			SpartanEngine::Color m_Color;
			float m_Progress;
		};
	}
}