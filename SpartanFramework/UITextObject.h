#pragma once
#include "UIObject.h"
#include "TextRenderComponent.h"

namespace Spartan
{
	namespace UI
	{
		class UITextObject : public UIObject
		{
		public:
			UITextObject();
			virtual ~UITextObject();

			BASIC_OBJECT(UITextObject, GameObject);

			TextRenderComponent* GetText();

		private:
			TextRenderComponent* m_pText;
		};
	}
}
