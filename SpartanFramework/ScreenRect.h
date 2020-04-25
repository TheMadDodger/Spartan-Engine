#pragma once
#include "SEObject.h"

namespace SpartanEngine
{
	class Mesh;
	class Material;
	class Renderer;
	class RenderTexture;

	class ScreenRect : public SEObject
	{
	private:
		ScreenRect();
		~ScreenRect();

	private:
		void RenderScreen(Renderer* pRenderer);
		void DrawScreenMesh();

	private:
		friend class Renderer;
		Material* m_pScreenRenderMaterial;
		GLuint m_ScreenQuadVertexbufferID;
	};
}