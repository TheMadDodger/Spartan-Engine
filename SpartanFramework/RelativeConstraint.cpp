#include "stdafx.h"
#include "RelativeConstraint.h"
#include "UIObject.h"
#include "Canvas.h"

namespace SpartanEngine
{
	namespace UI
	{
		RelativeConstraint::RelativeConstraint(float percentage) : m_Percentage(percentage) {}
		RelativeConstraint::~RelativeConstraint() {}

		void RelativeConstraint::UpdateConstraint(UIObject* pUIObject)
		{
			Canvas* pCanvas = pUIObject->GetParentCanvas();
			const Vector2& size = pCanvas->GetSize();
			m_Result = m_Axis == Axis::X ? size.x * m_Percentage : size.y * m_Percentage;
		}
	}
}