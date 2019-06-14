#pragma once
#include "BaseComponent.h"
class CameraComponent : public BaseComponent
{
public:
	CameraComponent();
	~CameraComponent();

	void SetAsActive();
	void Zoom(float factor);

	const Matrix3X3 &GetCameraMatrix() { return m_CameraMatrix; }
	const Matrix3X3 &GetCameraMatrixInverse() { return m_CameraInverseMatrix; }

	const Matrix3X3 &GetCameraProjectionMatrix() { return m_CameraProjectionMatrix; }
	const Matrix3X3 &GetCameraProjectionMatrixInverse() { return m_CameraProjectionInverseMatrix; }

	const Vector2 GetPosition();
	Vector3 ConvertWorldToScreenSpace(Vector3 worldCoord);

	virtual BaseComponent *Create() { return new CameraComponent(); }

protected:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	friend class GameScene;
	bool m_bActive = false;

	Matrix3X3 m_CameraMatrix;
	Matrix3X3 m_CameraInverseMatrix;

	Matrix3X3 m_CameraProjectionMatrix;
	Matrix3X3 m_CameraProjectionInverseMatrix;
};

