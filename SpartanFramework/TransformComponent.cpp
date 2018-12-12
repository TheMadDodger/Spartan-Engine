#include "stdafx.h"
#include "Components.h"
#include "GameObject.h"
#include "GameScene.h"

TransformComponent::TransformComponent() : m_TansformMatrix(Matrix3X3::CreateIdentityMatrix()), BaseComponent("Transform")
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void TransformComponent::Update(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	// Check if a rigid body is applied to this object
	auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
	if (pRigid)
	{
		Position = ToVector2(pRigid->Getb2Body()->GetPosition());
		Rotation = Vector3(0, 0, pRigid->Getb2Body()->GetAngle());
	}

	// Build own transform
	BuildTransform();

	// Apply parent transform if object has a parent
	auto pParent = GetGameObject()->GetParent();
	auto pUI = GetGameObject()->GetComponent<UIComponent>();
	if (pParent && pUI == nullptr)
	{
		auto parentTransformMatrix = pParent->GetTransform()->GetTransformMatrix();
		m_TansformMatrix = parentTransformMatrix * m_TansformMatrix;

		m_WorldPosition = m_TansformMatrix.ExtraxtTranslation();

		// We don't need to apply the camera transform again
		// That was already applied to our parent
		// So we can just return
		return;
	}

	m_WorldPosition = m_TansformMatrix.ExtraxtTranslation();

	// Don't apply camera transform if it's a UI Component
	if (pUI == nullptr)
	{
		auto camInverse = GetGameObject()->GetGameScene()->GetActiveCamera()->GetCameraMatrixInverse();
		m_TansformMatrix = camInverse * m_TansformMatrix;
	}
}

void TransformComponent::ApplyTransform()
{
	/// Applies the transform to OpenGL so everything rendered after it uses its transform
	// Extraxt all data from the Transform matrix
	Vector2 pos = m_TansformMatrix.ExtraxtTranslation();
	Vector2 scale = m_TansformMatrix.ExtraxtScale();
	Vector3 rot = m_TansformMatrix.ExtraxtRotation();
	
	// Convert rotation to Radians since OpenGL needs Radians
	rot.z = rot.z / M_PI * 180.0f;

	// Apply Transform to OpenGL
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(rot.z, 0, 0, 1);
	glScalef(scale.x, scale.y, 1);
}

void TransformComponent::BuildTransform()
{
	m_TansformMatrix = Matrix3X3::CreateScaleRotationTranslationMatrix(Position, Rotation, Scale);
}

const Matrix3X3 &TransformComponent::GetTransformMatrix()
{
	return m_TansformMatrix;
}

const Vector2 &TransformComponent::GetWorldPosition()
{
	return m_WorldPosition;
}

void TransformComponent::Translate(const Vector2 &position)
{
	Position = position;

	// Update rigid body if there is one
	auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
	if (pRigid)
	{
		pRigid->Getb2Body()->SetTransform(Tob2Vec2(Position), pRigid->Getb2Body()->GetAngle());
	}
}

void TransformComponent::Translate(float x, float y)
{
	Translate(Vector2(x, y));
}

void TransformComponent::Rotate(const Vector3 &rotation)
{
	Rotation = rotation;
	// Update rigid body if there is one
	auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
	if (pRigid)
	{
		pRigid->Getb2Body()->SetTransform(pRigid->Getb2Body()->GetPosition(), Rotation.z);
	}
}

void TransformComponent::SetScale(const Vector2 &scale)
{
	if (scale.x == 0 || scale.y == 0)
	{
		Utilities::Debug::LogWarning("TransformComponent::SetScale > A scale of 0 is not allowed!");
		return;
	}
	Scale = scale;
}

const Vector2 TransformComponent::GetPosition()
{
	return m_TansformMatrix.ExtraxtTranslation();
}
