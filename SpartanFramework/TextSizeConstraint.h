#pragma once
#include "BaseUIConstraint.h"

namespace SpartanEngine
{
	namespace UI
	{
		class TextSizeConstraint : public BaseUIConstraint
		{
		public:
			TextSizeConstraint();
			virtual ~TextSizeConstraint();

		private:
			void UpdateConstraint(UIObject* pUIObject) override;
		};
	}
}