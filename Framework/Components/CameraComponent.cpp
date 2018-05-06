#include "stdafx.h"
#include "../../stdafx.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "../Scenes/GameObject.h"
#include "../Scenes/GameScene.h"

CameraComponent::CameraComponent() : m_CameraMatrix(Matrix3X3::CreateIdentityMatrix()), m_CameraInverseMatrix(Matrix3X3::CreateIdentityMatrix())
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
	GetGameObject()->GetTransform()->SetScale(Vector2(1.0f / factor, 1.0f / factor));
}

const Vector2 CameraComponent::GetPosition()
{
	auto pTransform = GetGameObject()->GetTransform();
	auto camPos = pTransform->GetPosition();
	camPos.x += BaseGame::GetGame()->GetGameSettings().Window.Width / 2.0f;
	camPos.y += BaseGame::GetGame()->GetGameSettings().Window.Height / 2.0f;

	return camPos;
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

	/// Calculate the inverse matrix
	// Decompose matrix
	auto trans = m_CameraMatrix.ExtraxtTranslation();
	auto scale = m_CameraMatrix.ExtraxtScale();
	auto rot = m_CameraMatrix.ExtraxtRotation();

	if (scale.x == 0 || scale.y == 0)
	{
		Utilities::Debug::LogError("CameraComponent::Update > Camera scale is 0");
		return;
	}

	// Inverse each component and turn into a matrix
	trans = trans * -1;
	rot = rot * -1;
	scale.x = 1.0f / scale.x;
	scale.y = 1.0f / scale.y;

	auto transMat = Matrix3X3::CreateTranslationMatrix(trans);
	auto rotMat = Matrix3X3::CreateRotationMatrix(rot);
	auto scaleMat = Matrix3X3::CreateScalingMatrix(scale);

	// Multiply matrices in oposite order
	auto scaleRotMat = scaleMat * rotMat;
	auto scaleRotTransMat = scaleRotMat * transMat;

	auto window = BaseGame::GetGame()->GetGameSettings().Window;

	Vector2 screenMiddle = Vector2((float)window.Width, (float)window.Height) / 2.0f;

	auto screenTransform = Matrix3X3::CreateTranslationMatrix(screenMiddle);

	m_CameraInverseMatrix = screenTransform * scaleRotTransMat;
}

void CameraComponent::Draw(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
