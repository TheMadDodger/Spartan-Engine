#include "stdafx.h"
#include "BaseUIConstraint.h"

namespace SpartanEngine
{
	namespace UI
	{
		BaseUIConstraint::BaseUIConstraint() : m_Result(0.0f)
		{
		}

		BaseUIConstraint::~BaseUIConstraint()
		{
		}

		float BaseUIConstraint::FetchResult()
		{
			return m_Result;
		}

		void BaseUIConstraint::SetAxis(const Axis& axis)
		{
			m_Axis = axis;
		}
	}
}