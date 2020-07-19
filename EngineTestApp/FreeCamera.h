#pragma once
#include <GameObject.h>
class FreeCamera : public Spartan::GameObject
{
public:
	FreeCamera();
	virtual ~FreeCamera();

	float m_MaxDistance;

private:
	virtual void Initialize(const Spartan::GameContext &gameContext) override;
	virtual void Update(const Spartan::GameContext &gameContext) override;

private:
	Spartan::CameraComponent *m_pCameraComponent;
	float m_CurrentZoom = 1.0f;
	float m_DesiredZoom = 1.0f;
	Spartan::Vector3 m_FocusPos;
	Spartan::Vector2 m_MousePos;
	Spartan::Vector2 m_LastMouseDownPos;
	bool m_InputDisabled = false;
};

