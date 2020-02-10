#pragma once
#include "BaseComponent.h"
class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	~TransformComponent();

	/// DEPRECATED!!!
	/// USE SHADERS!!!
	void ApplyTransform();
	void BuildTransform();
	const Matrix4X4 &GetTransformMatrix();
	const Matrix4X4 &GetWorldMatrix();
	const Vector3 &GetWorldPosition();

	void Translate(const Vector3 &position, bool updateTransform = false);
	void Translate(const Vector2 &position, bool updateTransform = false);
	void Translate(float x, float y, float z, bool updateTransform = false);
	void Translate(float x, float y, bool updateTransform = false);
	void Rotate(const Vector3 &rotation, bool updateTransform = false);
	void SetScale(const Vector3 &scale, bool updateTransform = false);
	bool UseCamera();

	const Vector3 GetPositionInScreenSpace();

	Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
	Quaternion Rotation = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);

	COMPONENT_EDITOR(TransformComponent)

protected:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;

	void UpdateTransform();

private:
	Matrix4X4 m_TansformMatrix;
	Matrix4X4 m_WorldTansformMatrix;
	Vector3 m_WorldPosition;
	bool m_UseCamera = true;
};

