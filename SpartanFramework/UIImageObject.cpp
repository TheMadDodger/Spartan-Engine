#include "stdafx.h"
#include "UIImageObject.h"

namespace Spartan
{
	namespace UI
	{
		UIImageObject::UIImageObject()
		{
			m_pImage = CreateDefaultComponent<ImageRenderComponent>();
		}

		UIImageObject::~UIImageObject()
		{
		}

		ImageRenderComponent* UIImageObject::GetImage()
		{
			return m_pImage;
		}
	}
}