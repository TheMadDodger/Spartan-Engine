#pragma once
#include "BaseComponent.h"
class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	~TransformComponent();

	void ApplyTransform();
	void BuildTransform();
	const Matrix3X3 &GetTransformMatrix();
	const Matrix3X3 &GetWorldMatrix();
	const Vector2 &GetWorldPosition();

	void Translate(const Vector2 &position);
	void Translate(float x, float y);
	void Rotate(const Vector3 &rotation);
	void SetScale(const Vector2 &scale);
	bool UseCamera();

	const Vector2 GetPositionInScreenSpace();

	Vector2 Position = Vector2(0, 0);
	Vector3 Rotation = Vector3(0, 0, 0);
	Vector2 Scale = Vector2(1, 1);

	COMPONENT_EDITOR(TransformComponent)

protected:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;

private:

	Matrix3X3 m_TansformMatrix;
	Matrix3X3 m_WorldTansformMatrix;
	Vector2 m_WorldPosition;
	bool m_UseCamera = true;
};

