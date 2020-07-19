#pragma once
#include "BaseUIConstraint.h"

namespace Spartan
{
	namespace UI
	{
		class AspectConstraint : public BaseUIConstraint
		{
		public:
			AspectConstraint(float ratio);
			~AspectConstraint();

		private:
			void UpdateConstraint(UIObject* pUIObject) override;

		private:
			float m_Ratio;
		};
	}
}
