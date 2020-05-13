#pragma once
#include "UIObject.h"

class Material;

namespace SpartanEngine
{
	class RenderTexture;

	namespace UI
	{

		enum CanvasRenderMode
		{
			ScreenSpace,
			WorldSpace,
		};

		class Canvas : public UIObject
		{
		public:
			Canvas();
			virtual ~Canvas();

		public:
			void SetRenderMode(const CanvasRenderMode& renderMode);
			const Matrix4X4& GetProjectionMatrix();
			const CanvasRenderMode& GetRenderMode();

			const Matrix4X4& GetUIProjectionMatrix();

			void AutoResizeToScreen(bool enable);

			void SetColor(const Color& color);

		protected:
			void Initialize(const GameContext& gameContext) override;
			void Update(const GameContext& gameContext) override;
			void Draw(const GameContext& gameContext) override;

		private:
			void RootDraw(const GameContext& gameContext) override;
			void PostDraw(const GameContext& gameContext) override;
			void OnParentUpdated(GameObject* pNewParent) override;
			void UIHandleMouse(const Vector2& relativeMousePos) override;
			void OnResize(const Vector2& newDimensions) override;

			void CreateCanvasQuad();
			void DestroyGLData();
			void DrawCanvasMesh();
			void CalculateMatrices();
			void AutoResizeToScreenControl();

		private:
			RenderTexture* m_pRenderTexture;
			GLuint m_CanvasQuadVertexBufferID;
			Matrix4X4 m_CanvasMatrix;
			Matrix4X4 m_ProjectionMatrix;
			Matrix4X4 m_UIProjectionMatrix;
			Matrix4X4 m_CanvasProjectionMatrix;
			CanvasRenderMode m_RenderMode;
			GameObject* m_pLastParrent;
			Color m_Color;

		private:
			static Material* m_pCanvasRenderer;
			bool m_ResizeToScreen;
		};
	}
}