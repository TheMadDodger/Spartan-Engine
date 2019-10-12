#pragma once
#include <GameObject.h>
class FreeCamera : public GameObject
{
public:
	FreeCamera();
	virtual ~FreeCamera();

	float m_MaxDistance;

private:
	virtual void Initialize(const GameContext &gameContext) override;
	virtual void Update(const GameContext &gameContext) override;

private:
	CameraComponent *m_pCameraComponent;
	float m_CurrentZoom = 1.0f;
	float m_DesiredZoom = 1.0f;
	Vector2 m_FocusPos;
	Vector2 m_MousePos;
	Vector2 m_LastMouseDownPos;
	bool m_InputDisabled = false;
};

