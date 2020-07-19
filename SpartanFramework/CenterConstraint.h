#pragma once
#include "BaseUIConstraint.h"

namespace Spartan
{
	namespace UI
	{
		class UIObject;

		class CenterConstraint : public BaseUIConstraint
		{
		public:
			CenterConstraint();
			virtual ~CenterConstraint();

		private:
			void UpdateConstraint(UIObject* pUIObject) override;
		};
	}
}