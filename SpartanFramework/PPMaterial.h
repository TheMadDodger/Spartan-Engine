#pragma once
#include "Material.h"
#include "RenderTexture.h"

namespace SpartanEngine
{
	class PPMaterial : public Material
	{
	public:
		PPMaterial(ShaderData* pShader);
		~PPMaterial();

		void SetBaseTexture(RenderTexture* pRenderTexture);

	protected:
		virtual void SetShaderVars(RenderTexture* pRenderingFromTexture) = 0;

	private:
		friend class PostProcessingStack;
	};
}