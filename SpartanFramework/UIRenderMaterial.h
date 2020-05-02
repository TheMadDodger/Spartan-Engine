#pragma once
#include "Material.h"

namespace SpartanEngine
{
	class TextureData;

	namespace UI
	{
		class UIRenderMaterial : public Material
		{
		public:
			UIRenderMaterial(ShaderData* pShader);
			virtual ~UIRenderMaterial();

			void SetUITexture(TextureData* pTexture);
			void SetWorldProjection(const Matrix4X4& worldProjection);
			void SetOffsets(const Vector4& offsets);

		protected:
			void SetShaderVars(BaseComponent*);

		private:
			friend class UIComponent;
			TextureData* m_pTexture;
			Vector4 m_CenterOffsets;
			Matrix4X4 m_WorldProjection;
		};
	}
}