#include "stdafx.h"
#include "BasicCamera.h"
#include "CameraComponent.h"

namespace SpartanEngine
{
	BasicCamera::BasicCamera()
	{
		m_pCam = CreateDefaultComponent<CameraComponent>();
	}

	BasicCamera::~BasicCamera()
	{
	}

	void BasicCamera::Initialize(const GameContext& gameContext)
	{
		UNREFERENCED_PARAMETER(gameContext);
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