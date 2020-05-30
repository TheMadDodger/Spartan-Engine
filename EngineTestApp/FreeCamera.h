#pragma once
#include <GameObject.h>
class FreeCamera : public SpartanEngine::GameObject
{
public:
	FreeCamera();
	virtual ~FreeCamera();

	float m_MaxDistance;

private:
	virtual void Initialize(const SpartanEngine::GameContext &gameContext) override;
	virtual void Update(const SpartanEngine::GameContext &gameContext) override;

private:
	SpartanEngine::CameraComponent *m_pCameraComponent;
	float m_CurrentZoom = 1.0f;
	float m_DesiredZoom = 1.0f;
	SpartanEngine::Vector3 m_FocusPos;
	SpartanEngine::Vector2 m_MousePos;
	SpartanEngine::Vector2 m_LastMouseDownPos;
	bool m_InputDisabled = false;
};

