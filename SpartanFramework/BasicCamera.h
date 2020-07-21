#pragma once
#include "GameObject.h"

namespace Spartan
{
	class CameraComponent;

	class BasicCamera : public GameObject
	{
	public:
		BasicCamera();
		virtual ~BasicCamera();

		void Initialize(const GameContext& gameContext) override;
		void Update(const GameContext& gameContext) override;
		void Draw(const GameContext& gameContext) override;

		CameraComponent* GetCameraComponent();

	private:
		CameraComponent* m_pCam;
	};
}