#pragma once
#include "BaseUIConstraint.h"

namespace Spartan
{
	namespace UI
	{
		class RelativeConstraint : public BaseUIConstraint
		{
		public:
			RelativeConstraint(float percentage, bool relativeToCanvas = false);
			virtual ~RelativeConstraint();

			void SetPercentage(float percentage);

		private:
			void UpdateConstraint(UIObject* pUIObject) override;

		private:
			float m_Percentage;
			bool m_RelativeToCanvas;
		};
	}
}