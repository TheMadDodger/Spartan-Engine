#pragma once
#include "Material.h"

class TextureData;

class UIRenderMaterial : public Material
{
public:
	UIRenderMaterial(ShaderData* pShader);
	virtual ~UIRenderMaterial();

	void SetUITexture(TextureData* pTexture);
	void SetWorldProjection(const Matrix4X4& worldProjection);
	void SetAllignment(const Origin& allignment);

private:
	void SetShaderVars(BaseComponent *);

private:
	friend class UIComponent;
	TextureData* m_pTexture;
	Origin m_Allignment;
	Vector4 m_CenterOffsets;
	Matrix4X4 m_WorldProjection;
};
