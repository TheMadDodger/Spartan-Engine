#include "stdafx.h"
#include "BaseUIConstraint.h"

namespace Spartan
{
	namespace UI
	{
		BaseUIConstraint::BaseUIConstraint() : m_Result(0.0f), m_DebugEnabled(false)
		{
		}

		BaseUIConstraint::~BaseUIConstraint()
		{
		}

		float BaseUIConstraint::FetchResult()
		{
			return m_Result;
		}

		void BaseUIConstraint::EnableDebug(bool enabled)
		{
			m_DebugEnabled = enabled;
		}

		void BaseUIConstraint::SetAxis(const Axis& axis)
		{
			m_Axis = axis;
		}
	}
}