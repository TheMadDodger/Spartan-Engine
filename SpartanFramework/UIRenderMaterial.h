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
			void SetUIColor(const Color& color);

		protected:
			void SetShaderVars(BaseComponent*);

		protected:
			TextureData* m_pTexture;
			Vector4 m_CenterOffsets;
			Matrix4X4 m_WorldProjection;
			Color m_Color = Color::White();

		private:
			friend class UIComponent;
		};
	}
}