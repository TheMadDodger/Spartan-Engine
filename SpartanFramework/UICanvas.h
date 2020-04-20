#pragma once
#include "UIObject.h"

class RenderTexture;
class Material;

enum CanvasRenderMode
{
	ScreenSpace,
	WorldSpace,
};

class UICanvas : public UIObject
{
public:
	UICanvas();
	virtual ~UICanvas();

public:
	void SetSize(int width, int height);
	void SetRenderMode(const CanvasRenderMode &renderMode);
	const Matrix4X4& GetProjectionMatrix();
	const CanvasRenderMode& GetRenderMode();

	const Matrix4X4& GetUIProjectionMatrix();

private:
	void RootDraw(const GameContext& gameContext) override;
	void Initialize(const GameContext& gameContext) override;
	void Update(const GameContext& gameContext) override;
	void Draw(const GameContext& gameContext) override;
	void PostDraw(const GameContext& gameContext) override;
	void OnParentUpdated(GameObject* pNewParent) override;
	void UIHandleMouse(const Vector2& relativeMousePos) override;

	void CreateCanvasQuad();
	void DestroyGLData();
	void DrawCanvasMesh();
	void CalculateMatrices();

private:
	RenderTexture* m_pRenderTexture;
	IntVector2 m_Dimensions;
	GLuint m_CanvasQuadVertexBufferID;
	Matrix4X4 m_CanvasMatrix;
	Matrix4X4 m_ProjectionMatrix;
	Matrix4X4 m_UIProjectionMatrix;
	Matrix4X4 m_CanvasProjectionMatrix;
	CanvasRenderMode m_RenderMode;
	GameObject* m_pLastParrent;

private:
	static Material* m_pCanvasRenderer;
};

