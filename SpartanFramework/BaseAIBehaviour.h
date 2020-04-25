#pragma once
#include "SEObject.h"

namespace SpartanEngine
{
	class AIComponent;

	class BaseAIBehaviour : SEObject
	{
	public:
		BaseAIBehaviour();
		virtual ~BaseAIBehaviour();

		AIComponent* GetAIOwner();

		void SetOwner(AIComponent* pOwner);

		virtual void Initialize() = 0;
		virtual void Tick(float deltaTime) = 0;

	private:
		AIComponent* m_pAIOwner;
	};
}