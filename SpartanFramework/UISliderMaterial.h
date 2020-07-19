#pragma once
#include "UIRenderMaterial.h"

namespace Spartan
{
	namespace UI
	{
		class UISliderMaterial : public UIRenderMaterial
		{
		public:
			UISliderMaterial(ShaderData* pShader);
			~UISliderMaterial();

			void SetColor(const Spartan::Color& color);
			void SetProgress(float progress);

		private:
			void SetShaderVars(BaseComponent* pComponent) override;

		private:
			Spartan::Color m_Color;
			float m_Progress;
		};
	}
}