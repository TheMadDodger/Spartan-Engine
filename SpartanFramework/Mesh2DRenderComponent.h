#pragma once
#include "BaseComponent.h"

class Mesh2D;
class Material;

class Mesh2DRenderComponent : public BaseComponent
{
public:
	Mesh2DRenderComponent();
	virtual ~Mesh2DRenderComponent();

	void SetMesh(Mesh2D *pMesh);
	void SetMaterial(size_t materialID);

private:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

	COMPONENT_EDITOR(Mesh2DRenderComponent)

private:
	Mesh2D *m_pMesh;
	size_t m_MaterialID;
	GLuint gVBO;
	GLuint gIBO;
	GLuint gVertexPos2DLocation;
};

