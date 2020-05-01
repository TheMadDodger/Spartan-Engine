#pragma once
#include "UIObject.h"
#include "ImageRenderComponent.h"

namespace SpartanEngine
{
	namespace UI
	{
		class UIImageObject : public UIObject
		{
		public:
			UIImageObject();
			virtual ~UIImageObject();

			ImageRenderComponent* GetImage();

		private:
			ImageRenderComponent* m_pImage;
		};
	}
}
