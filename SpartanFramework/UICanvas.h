#pragma once
#include "GameObject.h"

class RenderTexture;
class Material;

enum CanvasRenderMode
{
	ScreenSpace,
	WorldSpace,
};

class UICanvas : public GameObject
{
public:
	UICanvas();
	virtual ~UICanvas();

public:
	void SetSize(int width, int height);
	void SetRenderMode(const CanvasRenderMode &renderMode);
	const Matrix4X4& GetProjectionMatrix();
	const CanvasRenderMode& GetRenderMode();

private:
	void Initialize(const GameContext& gameContext) override;
	void Update(const GameContext& gameContext) override;
	void Draw(const GameContext& gameContext) override;
	void PostDraw(const GameContext& gameContext) override;

	void CreateCanvasQuad();
	void DestroyGLData();
	void DrawCanvasMesh();
	void FindParentCanvas();
	void CalculateMatrices();

private:
	RenderTexture* m_pRenderTexture;
	IntVector2 m_Dimensions;
	GLuint m_CanvasQuadVertexBufferID;
	Matrix4X4 m_CanvasMatrix;
	Matrix4X4 m_ProjectionMatrix;
	Matrix4X4 m_CanvasProjectionMatrix;
	CanvasRenderMode m_RenderMode;
	UICanvas* m_pParentCanvas;
	GameObject* m_pLastParrent;

private:
	static Material* m_pCanvasRenderer;
};

