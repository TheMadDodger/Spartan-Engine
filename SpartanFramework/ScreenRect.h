#pragma once
#include "SEObject.h"

namespace Spartan
{
	class Mesh;
	class Material;
	class Renderer;
	class RenderTexture;

	class ScreenRect : public SEObject
	{
	public:
		void DrawScreenMesh();

		BASIC_OBJECT(ScreenRect, ScreenRect);

	private:
		ScreenRect();
		~ScreenRect();

	private:
		void RenderScreen(Renderer* pRenderer);

	private:
		friend class Renderer;
		Material* m_pScreenRenderMaterial;
		GLuint m_ScreenQuadVertexbufferID;
		GLuint m_ScreenQuadVertexArrayID;
	};
}