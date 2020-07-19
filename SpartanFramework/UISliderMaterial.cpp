#include "stdafx.h"
#include "UISliderMaterial.h"

namespace Spartan
{
	namespace UI
	{
		UISliderMaterial::UISliderMaterial(ShaderData* pShader) : UIRenderMaterial(pShader)
		{
		}

		UISliderMaterial::~UISliderMaterial()
		{
		}

		void UISliderMaterial::SetColor(const Spartan::Color& color)
		{
			m_Color = color;
		}

		void UISliderMaterial::SetProgress(float progress)
		{
			m_Progress = progress;
		}

		void UISliderMaterial::SetShaderVars(BaseComponent* pComponent)
		{
			UIRenderMaterial::SetShaderVars(pComponent);
			Material::SetColor("Color", m_Color);
			SetFloat("Progress", m_Progress);
		}
	}
}