#include "stdafx.h"
#include "RelativeConstraint.h"
#include "UIObject.h"
#include "Canvas.h"

namespace Spartan
{
	namespace UI
	{
		RelativeConstraint::RelativeConstraint(float percentage, bool relativeToCanvas) : m_Percentage(percentage), m_RelativeToCanvas(relativeToCanvas) {}
		RelativeConstraint::~RelativeConstraint() {}

		void RelativeConstraint::SetPercentage(float percentage)
		{
			m_Percentage = percentage;
		}

		void RelativeConstraint::UpdateConstraint(UIObject* pUIObject)
		{
			UIObject* pParent = (UIObject*)pUIObject->GetParent();
			if (pParent == nullptr || m_RelativeToCanvas)
			{
				pParent = pUIObject->GetParentCanvas();
			}
			const Vector2& size = pParent->GetSize();
			m_Result = m_Axis == Axis::X ? size.x * m_Percentage : size.y * m_Percentage;

			if (m_DebugEnabled)
			{
				Utilities::Debug::LogInfo("Size: " + to_string(size.x) + "," + to_string(size.y) + " - Result: " + to_string(m_Result));
			}
		}
	}
}