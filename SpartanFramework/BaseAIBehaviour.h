#pragma once
#include "SEObject.h"

namespace Spartan
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

		virtual const std::type_info& GetBaseType() override { return typeid(BaseAIBehaviour); }
		virtual const std::type_info& GetType() override { return typeid(BaseAIBehaviour); }

	private:
		AIComponent* m_pAIOwner;
	};
}