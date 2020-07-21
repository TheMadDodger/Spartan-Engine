#pragma once
#include "SEObject.h"

namespace Spartan
{
	class RenderTexture : SEObject
	{
	public: // Static functions
		static RenderTexture* CreateRenderTexture(int width, int height, bool hasDepthBuffer = true);
		static void Destroy(RenderTexture* pTexture);
		static void DestroyAll();
		static void UseDefaultRenderTexture();
		static RenderTexture* GetDefaultRenderTexture();
		static RenderTexture* GetUIRenderTexture();

		bool IsInUse();

	private: // Private static functions
		static void StartFinalRender();
		static void EndFinalRender();

	public: // Instance functions
		void Resize(int width, int height);
		void Use();
		void StopUse();
		const GLuint& GetTextureID();
		const IntVector2& GetDimensions();

	private: // Constructors
		RenderTexture(int width, int height, bool hasDepthBuffer);
		~RenderTexture();

	private: // Private Instance functions
		void Initialize();
		void DestroyGLData();
		void Bind();
		void UnBind();

	private: // Static members
		static std::vector<RenderTexture*> m_pRenderTextures;
		static std::list<RenderTexture*> m_pRenderTextureUsedList;
		static RenderTexture* m_pDefaultTexture;
		static RenderTexture* m_pUITexture;
		static RenderTexture* m_pCurrentlyInUse;

	private: // Instance members
		friend class EditorApp;
		friend class Renderer;
		friend class ScreenRect;
		friend class PostProcessingStack;
		IntVector2 m_Dimensions;
		GLuint m_GLFrameBufferID;
		GLuint m_GLDepthBufferID;
		GLuint m_GLTextureID;
		bool m_HasDepthBuffer;
	};
}