#pragma once
#include <GameScene.h>

class PlanetMaterial;

class RenderTestScene : public SpartanEngine::GameScene
{
public:
	RenderTestScene();
	virtual ~RenderTestScene();

private:
	virtual void Initialize(const SpartanEngine::GameContext& gameContext);
	virtual void Update(const SpartanEngine::GameContext& gameContext);
	virtual void Draw(const SpartanEngine::GameContext& gameContext);

private:
	float m_DesiredZ = 0.0f;
	float m_CameraYaw = 0.0f;
	float m_ObjectRot = 0.0f;
	float m_CameraPitch = 0.0f;
	SpartanEngine::GameObject* m_pObject;

	PlanetMaterial* m_pMaterial;

	static const GLfloat g_vertex_buffer_data[];
};
