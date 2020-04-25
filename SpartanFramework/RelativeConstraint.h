#pragma once
#include "BaseUIConstraint.h"

namespace SpartanEngine
{
	namespace UI
	{
		class RelativeConstraint : public BaseUIConstraint
		{
		public:
			RelativeConstraint(float percentage);
			virtual ~RelativeConstraint();

		private:
			void UpdateConstraint(UIObject* pUIObject) override;

		private:
			float m_Percentage;
		};
	}
}