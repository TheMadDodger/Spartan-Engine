#include "stdafx.h"
#include "CenterConstraint.h"
#include "UIObject.h"
#include "Canvas.h"

namespace SpartanEngine
{
	namespace UI
	{
		CenterConstraint::CenterConstraint() {}
		CenterConstraint::~CenterConstraint() {}

		void CenterConstraint::UpdateConstraint(UIObject* pUIObject)
		{
			Canvas* pCanvas = pUIObject->GetParentCanvas();
			const Vector2& size = pCanvas->GetSize();
			m_Result = m_Axis == Axis::X ? size.x / 2.0f : size.y / 2.0f;
		}
	}
}