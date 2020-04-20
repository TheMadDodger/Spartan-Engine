#include "stdafx.h"
#include "Components.h"
#include "GameObject.h"
#include "GameScene.h"
#include "Layers.h"
#include "UICanvas.h"

TransformComponent::TransformComponent() : m_TansformMatrix(Matrix4X4::CreateIdentityMatrix()), BaseComponent("Transform")
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Initialize(const GameContext&)
{
	UpdateTransform();
}

void TransformComponent::Update(const GameContext&)
{
	UpdateTransform();
}

void TransformComponent::UpdateTransform()
{
	// Check if a rigid body is applied to this object
	auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
	if (pRigid)
	{
		Vector2 rigidPos = ToVector2(pRigid->Getb2Body()->GetPosition());
		Position = Vector3(rigidPos.x, rigidPos.y, Position.z);
		// TODO: Convert euler angle to Quaternion
		//Rotation = Vector3(0, 0, pRigid->Getb2Body()->GetAngle());
	}

	// Build own transform
	BuildTransform();

	// Apply parent transform if object has a parent
	auto pParent = GetGameObject()->GetParent();

	bool isCanvas = dynamic_cast<UICanvas*>(pParent) != nullptr;
	if (pParent && !isCanvas)
	{
		auto parentWorldTransformMatrix = pParent->GetTransform()->GetWorldMatrix();
		m_WorldTansformMatrix = m_TansformMatrix * parentWorldTransformMatrix;

		m_WorldPosition = m_WorldTansformMatrix.ExtraxtTranslation();

		auto parentTransformMatrix = pParent->GetTransform()->GetTransformMatrix();
		m_TansformMatrix = m_TansformMatrix * parentTransformMatrix;
		return;
	}

	m_WorldPosition = Position;
}

/// DEPRECATED!!!
/// USE SHADERS!!!
void TransformComponent::ApplyTransform()
{
	/// Applies the transform to OpenGL so everything rendered after it uses its transform
	// Extraxt all data from the Transform matrix
	Vector3 pos = m_TansformMatrix.ExtraxtTranslation();
	Vector3 scale = m_TansformMatrix.ExtraxtScale();
	Quaternion rot = m_TansformMatrix.ExtraxtRotation();

	// Convert rotation to Radians since OpenGL needs Radians
	//rot.z = rot.z / (float)M_PI * 180.0f;

	// Apply Transform to OpenGL
	glTranslatef(pos.x, pos.y, 0);
	//glRotatef(rot.z, 0, 0, 1);
	glScalef(scale.x, scale.y, 1);
}

void TransformComponent::BuildTransform()
{
	m_TansformMatrix = Matrix4X4::CreateScaleRotationTranslationMatrix(Position, Rotation, Scale);
	m_LocalTansformMatrix = m_TansformMatrix;
	m_WorldTansformMatrix = m_TansformMatrix;
}

const Matrix4X4 &TransformComponent::GetTransformMatrix()
{
	return m_TansformMatrix;
}

const Matrix4X4& TransformComponent::GetLocalTransformMatrix()
{
	return m_LocalTansformMatrix;
}

const Matrix4X4 &TransformComponent::GetWorldMatrix()
{
	return m_WorldTansformMatrix;
}

Matrix3X3 TransformComponent::GetRotationMatrix()
{
	return Matrix3X3(m_WorldTansformMatrix);
}

const Vector3 &TransformComponent::GetWorldPosition()
{
	return m_WorldPosition;
}

void TransformComponent::Translate(const Vector3 &position, bool updateTransform)
{
	Position = position;

	// Update rigid body if there is one
	auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
	if (pRigid && pRigid->IsInitialized())
	{

		pRigid->Getb2Body()->SetTransform(b2Vec2(Position.x, Position.y), pRigid->Getb2Body()->GetAngle());
	}

	if (updateTransform) UpdateTransform();
	GetGameObject()->SetDirty();
}

void TransformComponent::Translate(const Vector2 &position, bool updateTransform)
{
	Translate(Vector3(position.x, position.y, Position.z), updateTransform);
}

void TransformComponent::Translate(float x, float y, float z, bool updateTransform)
{
	Translate(Vector3(x, y, z), updateTransform);
}

void TransformComponent::Translate(float x, float y, bool updateTransform)
{
	Translate(Vector3(x, y, Position.z), updateTransform);
}

void TransformComponent::Rotate(const Vector3 &rotation, bool updateTransform)
{
	Rotation = Quaternion::Euler(rotation);
	// Update rigid body if there is one
	auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
	if (pRigid)
	{
		pRigid->Getb2Body()->SetTransform(pRigid->Getb2Body()->GetPosition(), Rotation.z);
	}

	if (updateTransform) UpdateTransform();
	GetGameObject()->SetDirty();
}

void TransformComponent::SetScale(const Vector3 &scale, bool updateTransform)
{
	if (scale.x == 0 || scale.y == 0 || scale.z == 0)
	{
		Utilities::Debug::LogWarning("TransformComponent::SetScale > A scale of 0 is not allowed!");
		return;
	}
	Scale = scale;

	if (updateTransform) UpdateTransform();
	GetGameObject()->SetDirty();
}

const Vector3 TransformComponent::GetPositionInScreenSpace()
{
	return m_TansformMatrix.ExtraxtTranslation();
}
