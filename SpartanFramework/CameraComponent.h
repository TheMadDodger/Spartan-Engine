#pragma once
#include "BaseComponent.h"

namespace SpartanEngine
{
	class CameraComponent : public BaseComponent
	{
	public:
		CameraComponent();
		~CameraComponent();

		void SetPerspective(float fov, float zNear, float zFar);
		void SetOrthographic(float nearPlane, float farPlane);

		void SetAsActive();
		void Zoom(float factor);

		const Matrix4X4& GetCameraMatrix() { return m_CameraMatrix; }
		const Matrix4X4& GetCameraMatrixInverse() { return m_CameraInverseMatrix; }

		const Matrix4X4& GetCameraProjectionMatrix() { return m_CameraProjectionMatrix; }
		const Matrix4X4& GetCameraProjectionMatrixInverse() { return m_CameraProjectionInverseMatrix; }

		const Matrix4X4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
		const Matrix4X4& GetViewProjectionMatrixInverse() { return m_ViewProjectionMatrixInverse; }

		const Matrix4X4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const Matrix4X4& GetProjectionMatrixInverse() { return m_ProjectionInverseMatrix; }

		const Matrix4X4& GetScreenMatrix() { return m_ScreenMatrix; }

		const Vector3 GetPosition();
		Vector3 ConvertWorldToScreenSpace(Vector3 worldCoord);

		virtual BaseComponent* Create() { return new CameraComponent(); }

		Ray ScreenPointToRay(const Vector2& screenPoint);

	protected:
		void Initialize(const GameContext& gameContext) override;
		void Update(const GameContext& gameContext) override;
		void Draw(const GameContext& gameContext) override;

	private:
		friend class GameScene;
		bool m_bActive = false;

		Matrix4X4 m_CameraMatrix;
		Matrix4X4 m_CameraInverseMatrix;

		Matrix4X4 m_ViewProjectionMatrix;
		Matrix4X4 m_ViewProjectionMatrixInverse;

		Matrix4X4 m_CameraProjectionMatrix;
		Matrix4X4 m_CameraProjectionInverseMatrix;

		Matrix4X4 m_ProjectionMatrix;
		Matrix4X4 m_ProjectionInverseMatrix;

		Matrix4X4 m_ScreenMatrix;

		float m_Near;
		float m_Far;
		float m_FOV;
	};
}