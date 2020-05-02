#include "stdafx.h"
#include "TextSizeConstraint.h"
#include "UIObject.h"
#include "Canvas.h"

namespace SpartanEngine
{
	namespace UI
	{
		TextSizeConstraint::TextSizeConstraint()
		{
		}

		TextSizeConstraint::~TextSizeConstraint()
		{
		}

		void TextSizeConstraint::UpdateConstraint(UIObject* pUIObject)
		{
			Vector2 mySize = pUIObject->GetOriginalSize();
			auto originalSize = pUIObject->GetParentCanvas()->GetOriginalSize();
			auto size = pUIObject->GetParentCanvas()->GetSize();
			Vector2 scales = size / originalSize;
			m_Result = m_Axis == Axis::X ? mySize.x * scales.x : mySize.y * scales.y;
		}
	}
}