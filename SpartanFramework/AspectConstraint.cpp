#include "stdafx.h"
#include "AspectConstraint.h"
#include "UIObject.h"

namespace SpartanEngine
{
	namespace UI
	{
		AspectConstraint::AspectConstraint(float ratio) : m_Ratio(ratio) {}
		AspectConstraint::~AspectConstraint() {}

		void AspectConstraint::UpdateConstraint(UIObject* pUIObject)
		{
			const Vector2& size = pUIObject->GetSize();
			m_Result = m_Axis == Axis::X ? size.y * m_Ratio : size.x * m_Ratio;
		}
	}
}