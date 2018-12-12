#include "stdafx.h"
#include "BasicCamera.h"
#include "CameraComponent.h"

BasicCamera::BasicCamera()
{
}

BasicCamera::~BasicCamera()
{
}

void BasicCamera::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	if(GetAllComponents().size() <= 1)
		AddComponent(new CameraComponent());
}

void BasicCamera::Update(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void BasicCamera::Draw(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
