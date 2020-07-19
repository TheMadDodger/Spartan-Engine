#include "stdafx.h"
#include "FreeCamera.h"
#include <Components.h>
#include <InputManager.h>

FreeCamera::FreeCamera() : m_MaxDistance(10.0f)
{
	m_pCameraComponent = CreateDefaultComponent<Spartan::CameraComponent>();
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::Initialize(const Spartan::GameContext &gameContext)
{
	gameContext.pInput->AddInputAction(Spartan::InputAction("MousePressed", Spartan::InputType::Pressed, 0, SDL_BUTTON_RIGHT));
	gameContext.pInput->AddInputAction(Spartan::InputAction("MouseDown", Spartan::InputType::Down, 0, SDL_BUTTON_RIGHT));
	gameContext.pInput->AddInputAction(Spartan::InputAction("RMousePressed", Spartan::InputType::Pressed, 0, SDL_BUTTON_LEFT));
}

void FreeCamera::Update(const Spartan::GameContext &gameContext)
{
	if (m_FocusPos.Magnitude() >= m_MaxDistance)
	{
		m_FocusPos = m_FocusPos.Normalized() * m_MaxDistance;
	}

	if (m_CurrentZoom < 0.5f) m_CurrentZoom = 0.5f;
	if (m_CurrentZoom > 10.0f) m_CurrentZoom = 5.0f;

	m_CurrentZoom = Spartan::Lerp(m_CurrentZoom, m_DesiredZoom, 0.1f);
	GetComponent<Spartan::CameraComponent>()->Zoom(m_CurrentZoom);

	GetTransform()->Position = Spartan::Vector3::Lerp(GetTransform()->Position, m_FocusPos, 0.01f);

	if (m_InputDisabled) return;

	if (gameContext.pInput->IsActionTriggered("MousePressed"))
	{
		m_LastMouseDownPos = gameContext.pInput->GetMouseScreenPosition();
	}
	if (gameContext.pInput->IsActionTriggered("MouseDown"))
	{
		m_MousePos = gameContext.pInput->GetMouseScreenPosition();
		auto diff = (m_LastMouseDownPos - m_MousePos) * (1.f / m_CurrentZoom);
		m_LastMouseDownPos = gameContext.pInput->GetMouseScreenPosition();
		m_FocusPos = m_FocusPos + diff;
	}

	float mouseWheel = gameContext.pInput->GetMouseWheelMovement().y;

	if (mouseWheel != 0)
	{
		int sign = Spartan::Math::Absolute<float>(mouseWheel);
		float zoomFactor;
		if (m_DesiredZoom >= 2.5f)
		{
			zoomFactor = 1.0f;
		}
		else if (m_DesiredZoom >= 1.0f)
		{
			zoomFactor = 0.5f;
		}
		else
		{
			zoomFactor = 0.1f;
		}

		m_DesiredZoom += (float)sign * zoomFactor;
		if (m_DesiredZoom < 0.5f)
		{
			m_DesiredZoom = 0.5f;
		}
		if (m_DesiredZoom > 10.0f)
		{
			m_DesiredZoom = 10.0f;
		}
	}
}
