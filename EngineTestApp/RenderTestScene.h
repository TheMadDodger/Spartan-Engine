#pragma once
#include <GameScene.h>

class PlanetMaterial;

class RenderTestScene : public Spartan::GameScene
{
public:
	RenderTestScene();
	virtual ~RenderTestScene();

private:
	virtual void Initialize(const Spartan::GameContext& gameContext);
	virtual void Update(const Spartan::GameContext& gameContext);
	virtual void Draw(const Spartan::GameContext& gameContext);

private:
	float m_DesiredZ = 0.0f;
	float m_CameraYaw = 0.0f;
	float m_ObjectRot = 0.0f;
	float m_CameraPitch = 0.0f;
	Spartan::GameObject* m_pObject;

	PlanetMaterial* m_pMaterial;

	static const GLfloat g_vertex_buffer_data[];
};
