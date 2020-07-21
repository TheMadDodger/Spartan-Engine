#include "stdafx.h"
#include "BasicCamera.h"
#include "CameraComponent.h"

namespace Spartan
{
	BasicCamera::BasicCamera() : GameObject("Camera")
	{
		m_pCam = CreateDefaultComponent<CameraComponent>();
	}

	BasicCamera::~BasicCamera()
	{
	}

	void BasicCamera::Initialize(const GameContext& gameContext)
	{
		UNREFERENCED_PARAMETER(gameContext);
		m_pCam->SetPerspective(60.0f, 0.1f, 999999999.0f);
	}

	void BasicCamera::Update(const GameContext& gameContext)
	{
		UNREFERENCED_PARAMETER(gameContext);
	}

	void BasicCamera::Draw(const GameContext& gameContext)
	{
		UNREFERENCED_PARAMETER(gameContext);
	}

	CameraComponent* BasicCamera::GetCameraComponent()
	{
		return m_pCam;
	}
}