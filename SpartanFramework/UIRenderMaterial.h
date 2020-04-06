#pragma once
#include "Material.h"

class TextureData;

class UIRenderMaterial : public Material
{
public:
	UIRenderMaterial(ShaderData* pShader);
	virtual ~UIRenderMaterial();

	void SetUITexture(TextureData* pTexture);
	void SetAllignment(const Origin& allignment);

private:
	void SetShaderVars(BaseComponent *);

private:
	TextureData* m_pTexture;
	Origin m_Allignment;
	Vector4 m_CenterOffsets;
	Matrix4X4 m_WorldProjection;
};
