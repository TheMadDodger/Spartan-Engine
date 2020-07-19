#include "stdafx.h"
#include "Components.h"
#include "GameObject.h"
#include "GameScene.h"
#include "Layers.h"
#include "Canvas.h"
#include "PhysicsObjectComponent.h"

namespace Spartan
{
	TransformComponent::TransformComponent() : m_TansformMatrix(Matrix4X4::CreateIdentityMatrix()),
		m_LocalTansformMatrix(Matrix4X4::CreateIdentityMatrix()),
		m_WorldTansformMatrix(Matrix4X4::CreateIdentityMatrix()), BaseComponent("Transform")
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
		//auto pRigid = GetGameObject()->GetComponent<RigidBody2DComponent>();
		//if (pRigid)
		//{
		//	Vector2 rigidPos = ToVector2(pRigid->Getb2Body()->GetPosition());
		//	Position = Vector3(rigidPos.x, rigidPos.y, Position.z);
		//	// TODO: Convert euler angle to Quaternion
		//	//Rotation = Vector3(0, 0, pRigid->Getb2Body()->GetAngle());
		//}

		// Build own transform
		BuildTransform();

		// Apply parent transform if object has a parent
		auto pParent = GetGameObject()->GetParent();

		bool isCanvas = dynamic_cast<UI::Canvas*>(pParent) != nullptr;
		if (pParent && !isCanvas)
		{
			auto parentWorldTransformMatrix = pParent->GetTransform()->GetWorldMatrix();
			m_WorldTansformMatrix = m_TansformMatrix * parentWorldTransformMatrix;

			m_WorldPosition = m_WorldTansformMatrix.ExtraxtTranslation();

			auto parentTransformMatrix = pParent->GetTransform()->GetTransformMatrix();
			m_TansformMatrix = m_TansformMatrix * parentTransformMatrix;

			if (m_TransformChanged)
			{
				auto pPhysicsObject = GetGameObject()->GetComponent<PhysicsObjectComponent>();
				if (pPhysicsObject)
				{
					pPhysicsObject->UpdateTransform(m_WorldPosition, Rotation, Scale);
				}
				m_TransformChanged = false;
			}

			return;
		}

		m_WorldPosition = Position;

		if (m_TransformChanged)
		{
			auto pPhysicsObject = GetGameObject()->GetComponent<PhysicsObjectComponent>();
			if (pPhysicsObject)
			{
				pPhysicsObject->UpdateTransform(m_WorldPosition, Rotation, Scale);
			}
			m_TransformChanged = false;
		}
	}

	void TransformComponent::UpdateAllTransforms()
	{
		auto pParent = GetGameObject()->GetParent();
		if (pParent) pParent->GetTransform()->UpdateAllTransforms();
		UpdateTransform();
	}

	void TransformComponent::TransformChanged()
	{
		m_TransformChanged = true;
		const std::vector<Spartan::GameObject*>& pChildren = GetGameObject()->GetChildren();

		std::for_each(pChildren.begin(), pChildren.end(), [](Spartan::GameObject* pObject)
		{pObject->GetTransform()->TransformChanged(); });
	}

	void TransformComponent::BuildTransform()
	{
		m_TansformMatrix = Matrix4X4::CreateScaleRotationTranslationMatrix(Position, Rotation, Scale);
		m_LocalTansformMatrix = m_TansformMatrix;
		m_WorldTansformMatrix = m_TansformMatrix;
	}

	const Matrix4X4& TransformComponent::GetTransformMatrix() const
	{
		return m_TansformMatrix;
	}

	const Matrix4X4& TransformComponent::GetLocalTransformMatrix() const
	{
		return m_LocalTansformMatrix;
	}

	const Matrix4X4& TransformComponent::GetWorldMatrix() const
	{
		return m_WorldTansformMatrix;
	}

	Matrix3X3 TransformComponent::GetRotationMatrix() const
	{
		return Matrix3X3(m_WorldTansformMatrix);
	}

	const Vector3& TransformComponent::GetWorldPosition() const
	{
		return m_WorldPosition;
	}

	void TransformComponent::SetWorldPosition(const Vector3& position)
	{
		auto pParent = GetGameObject()->GetParent();
		if (!pParent)
		{
			Position = position;
			return;
		}
		Vector3 localPosition = position - pParent->GetTransform()->GetWorldPosition();
		Position = position;

		TransformChanged();
	}

	const Vector3& TransformComponent::GetLocalPosition() const
	{
		return Position;
	}

	const Quaternion& TransformComponent::GetLocalRotation() const
	{
		return Rotation;
	}

	const Vector3& TransformComponent::GetLocalScale() const
	{
		return Scale;
	}

	void TransformComponent::Translate(const Vector3& position, bool updateTransform)
	{
		Position = position;

		// Update rigid body if there is one
		//auto pRigid = GetGameObject()->GetComponent<RigidBody2DComponent>();
		//if (pRigid && pRigid->IsInitialized())
		//{
		//	pRigid->Getb2Body()->SetTransform(b2Vec2(Position.x, Position.y), pRigid->Getb2Body()->GetAngle());
		//}
		TransformChanged();

		if (updateTransform) UpdateTransform();
		GetGameObject()->SetDirty();
	}

	void TransformComponent::Translate(const Vector2& position, bool updateTransform)
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

	void TransformComponent::Rotate(const Vector3& rotation, bool updateTransform)
	{
		Rotation = Quaternion::Euler(rotation);
		// Update rigid body if there is one
		auto pRigid = GetGameObject()->GetComponent<RigidBody2DComponent>();
		if (pRigid)
		{
			pRigid->Getb2Body()->SetTransform(pRigid->Getb2Body()->GetPosition(), Rotation.z);
		}

		TransformChanged();

		if (updateTransform) UpdateTransform();
		GetGameObject()->SetDirty();
	}

	void TransformComponent::SetScale(const Vector3& scale, bool updateTransform)
	{
		if (scale.x == 0 || scale.y == 0 || scale.z == 0)
		{
			Utilities::Debug::LogWarning("TransformComponent::SetScale > A scale of 0 is not allowed!");
			return;
		}
		Scale = scale;

		TransformChanged();

		if (updateTransform) UpdateTransform();
		GetGameObject()->SetDirty();
	}

	void TransformComponent::SetRotation(const Quaternion& rotation, bool updateTransform)
	{
		Rotation = rotation;
		TransformChanged();

		if (updateTransform) UpdateTransform();
		GetGameObject()->SetDirty();
	}

	const Vector3 TransformComponent::GetPositionInScreenSpace()
	{
		return m_TansformMatrix.ExtraxtTranslation();
	}
}