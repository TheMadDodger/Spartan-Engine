#pragma once
#include "Material.h"
#include "TextureData.h"

namespace Spartan
{
	namespace UI
	{
		class UIRenderMaterial : public Material
		{
		public:
			UIRenderMaterial(ShaderData* pShader);
			virtual ~UIRenderMaterial();

			void SetUITexture(TextureData* pTexture);
			void SetWorldProjection(const Math::Matrix4X4& worldProjection);
			void SetOffsets(const Math::Vector4& offsets);
			void SetUIColor(const Math::Color& color);

		protected:
			void SetShaderVars(BaseComponent*);

		protected:
			TextureData* m_pTexture;
			Math::Vector4 m_CenterOffsets;
			Math::Matrix4X4 m_WorldProjection;
			Math::Color m_Color = Math::Color::White();

		private:
			friend class UIComponent;
		};
	}
}