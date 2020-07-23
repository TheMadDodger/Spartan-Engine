#pragma once
#include "BaseComponent.h"

namespace Spartan
{
	namespace UI
	{
		class Constraints;
	}

	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();
		~TransformComponent();

		void BuildTransform();
		const Matrix4X4& GetTransformMatrix() const;
		const Matrix4X4& GetLocalTransformMatrix() const;
		const Matrix4X4& GetWorldMatrix() const;
		Matrix3X3 GetRotationMatrix() const;
		const Vector3& GetWorldPosition() const;
		void SetWorldPosition(const Vector3& position);

		const Vector3& GetLocalPosition() const;
		const Quaternion& GetLocalRotation() const;
		const Vector3& GetLocalScale() const;

		void Translate(const Vector3& position, bool updateTransform = false);
		void Translate(const Vector2& position, bool updateTransform = false);
		void Translate(float x, float y, float z, bool updateTransform = false);
		void Translate(float x, float y, bool updateTransform = false);
		void Rotate(const Vector3& rotation, bool updateTransform = false);
		void SetScale(const Vector3& scale, bool updateTransform = false);
		void SetRotation(const Quaternion& scale, bool updateTransform = false);

		const Vector3 GetPositionInScreenSpace();

		// WARNING! Editing this value does not update any physics components on this object!
		Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
		// WARNING! Editing this value does not update any physics components on this object!
		Quaternion Rotation = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		// WARNING! Editing this value does not update any physics components on this object!
		Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);

		COMPONENT_EDITOR(TransformComponent)

	protected:
		void Initialize(const GameContext& gameContext) override;
		void Update(const GameContext& gameContext) override;

		void UpdateTransform();

	private:
		void UpdateAllTransforms();

		void TransformChanged();

		virtual void DefineSerializedProperties(std::vector<Serialization::SerializedProperty>& params) override;

	private:
		friend class PhysicsObjectComponent;
		Matrix4X4 m_TansformMatrix;
		Matrix4X4 m_LocalTansformMatrix;
		Matrix4X4 m_WorldTansformMatrix;
		Vector3 m_WorldPosition;

		bool m_TransformChanged = false;
	};
}