#pragma once
#include "BaseUIConstraint.h"

namespace Spartan
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