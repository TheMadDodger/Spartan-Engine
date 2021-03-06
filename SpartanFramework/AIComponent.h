#pragma once
#include "BaseComponent.h"
#include "BaseAIBehaviour.h"

namespace SpartanEngine
{
	class AIComponent : public BaseComponent
	{
	public:
		AIComponent();
		virtual ~AIComponent();

		void SetBehaviour(BaseAIBehaviour* pBehaviour);

	private:
		virtual void Initialize(const GameContext&) override;
		virtual void Update(const GameContext& gameContext) override;

		COMPONENT_EDITOR(AIComponent)

	private:
		BaseAIBehaviour* m_pAIBehaviour;
	};
}