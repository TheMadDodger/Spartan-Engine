#include "stdafx.h"
#include "PixelConstraint.h"

namespace Spartan
{
	namespace UI
	{
		PixelConstraint::PixelConstraint(float pixels) : m_Pixels(pixels) {}
		PixelConstraint::~PixelConstraint() {}

		void PixelConstraint::UpdateConstraint(UIObject* pUIObject)
		{
			m_Result = m_Pixels;
		}
	}
}