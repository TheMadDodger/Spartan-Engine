#include "stdafx.h"
#include "PPMaterial.h"

namespace Spartan
{
	PPMaterial::PPMaterial(ShaderData* pShader) : Material(pShader)
	{
	}

	PPMaterial::~PPMaterial()
	{
	}

	void PPMaterial::SetBaseTexture(RenderTexture* pRenderTexture)
	{
		SetTexture("BaseTexture", pRenderTexture->GetTextureID());
	}
}