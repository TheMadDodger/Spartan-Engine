#pragma once
#include "BaseUIConstraint.h"
namespace Spartan
{
	namespace UI
	{
		class PixelConstraint : public BaseUIConstraint
		{
		public:
			PixelConstraint(float pixels);
			virtual ~PixelConstraint();

		private:
			void UpdateConstraint(UIObject* pUIObject) override;

		private:
			float m_Pixels;
		};
	}
}