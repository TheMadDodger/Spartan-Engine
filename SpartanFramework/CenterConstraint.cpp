#include "stdafx.h"
#include "CenterConstraint.h"
#include "UIObject.h"
#include "Canvas.h"

namespace Spartan
{
	namespace UI
	{
		CenterConstraint::CenterConstraint() {}
		CenterConstraint::~CenterConstraint() {}

		void CenterConstraint::UpdateConstraint(UIObject* pUIObject)
		{
			UIObject* pParent = (UIObject*)pUIObject->GetParent();
			if (pParent == nullptr)
			{
				pParent = pUIObject->GetParentCanvas();
			}
			const Vector2& size = pParent->GetSize();
			m_Result = m_Axis == Axis::X ? size.x / 2.0f : size.y / 2.0f;
		}
	}
}