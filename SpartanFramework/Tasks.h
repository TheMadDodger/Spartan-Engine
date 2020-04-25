#pragma once
#include "AI.h"

namespace SpartanEngine
{
	class BTWaitTask : public BTTaskNode
	{
	public:
		BTWaitTask(float waitTime = 1.0f) : m_WaitTime(waitTime), m_Timer(0.0f) {};
		virtual ~BTWaitTask() {};

	private:
		virtual BTNodeResult ExecuteTask(Blackboard*) override
		{
			m_Timer = 0.0f;
			return BTNodeResult::BTInProgress;
		}

		virtual void TickTask(float deltaTime, Blackboard* pBlackboard) override
		{
			m_Timer += deltaTime;
			if (m_Timer >= m_WaitTime)
			{
				m_Timer = 0.0f;
				FinishTask(BTNodeResult::BTSucces);
			}
		}

	private:
		float m_WaitTime;
		float m_Timer;
	};
}