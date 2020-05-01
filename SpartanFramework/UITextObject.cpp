#include "stdafx.h"
#include "UITextObject.h"

namespace SpartanEngine
{
	namespace UI
	{
		UITextObject::UITextObject()
		{
			m_pText = CreateDefaultComponent<TextRenderComponent>();
		}

		UITextObject::~UITextObject()
		{
		}

		TextRenderComponent* UITextObject::GetText()
		{
			return m_pText;
		}
	}
}