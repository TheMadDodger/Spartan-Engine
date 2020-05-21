#pragma once
#include "UIRenderMaterial.h"

namespace SpartanEngine
{
	namespace UI
	{
		class LineRenderMaterial : public UIRenderMaterial
		{
		public:
			LineRenderMaterial(ShaderData* pShader);
			virtual ~LineRenderMaterial();

			void SetStartAndEnd(Vector2 startPos, Vector2 endPos);
			void SetLineWidth(float width);

		private:
			void SetShaderVars(BaseComponent*);

		private:
			Vector4 m_LineRect;
			float m_LineWidth;
		};
	}
}
