#include "stdafx.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameScene.h"

CameraComponent::CameraComponent() : m_CameraMatrix(Matrix4X4::CreateIdentityMatrix()), m_CameraInverseMatrix(Matrix4X4::CreateIdentityMatrix()), BaseComponent("Camera")
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::SetAsActive()
{
	GetGameObject()->GetGameScene()->SetActiveCamera(this);
	m_bActive = true;
}

void CameraComponent::Zoom(float factor)
{
	if (factor == 0.0f)
	{
		Utilities::Debug::LogWarning("A zoom factor of 0 is not allowed!");
		return;
	}
	GetGameObject()->GetTransform()->SetScale(Vector3(1.0f / factor, 1.0f / factor, 1.0f / factor));
}

const Vector3 CameraComponent::GetPosition()
{
	auto pTransform = GetGameObject()->GetTransform();
	auto camPos = pTransform->GetPositionInScreenSpace();
	camPos.x += BaseGame::GetGame()->GetGameSettings().Window.Width / 2.0f;
	camPos.y += BaseGame::GetGame()->GetGameSettings().Window.Height / 2.0f;

	return camPos;
}

Vector3 CameraComponent::ConvertWorldToScreenSpace(Vector3 worldCoord)
{
	return m_CameraInverseMatrix * worldCoord;
}

void CameraComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void CameraComponent::Update(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	GetGameObject()->GetTransform()->BuildTransform();
	m_CameraMatrix = GetGameObject()->GetTransform()->GetTransformMatrix();

	auto window = BaseGame::GetGame()->GetGameSettings().Window;
	auto view = Vector3((float)window.Width, (float)window.Height, 1.0f);
	m_ProjectionMatrix = Matrix4X4::CreateScalingMatrix(view / 2.0f);
	m_CameraProjectionMatrix = m_CameraMatrix * m_ProjectionMatrix;
	/// Calculate the inverse matrix
	Vector3 screenMiddle = Vector3((float)window.Width, (float)window.Height, 2.0f) / 2.0f;

	auto screenTransform = Matrix4X4::CreateTranslationMatrix(screenMiddle);

	m_CameraInverseMatrix = screenTransform * m_CameraMatrix.Inverse();
	m_CameraProjectionInverseMatrix = m_CameraProjectionMatrix.Inverse();
	m_ProjectionInverseMatrix = m_ProjectionMatrix.Inverse();
}

void CameraComponent::Draw(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
