#pragma once

namespace SpartanEngine
{
	namespace UI
	{
		class BaseUIConstraint;
		class UIObject;

		class Constraints
		{
		public:
			void SetX(BaseUIConstraint* pConstraint);
			void SetY(BaseUIConstraint* pConstraint);
			void SetWidth(BaseUIConstraint* pConstraint);
			void SetHeight(BaseUIConstraint* pConstraint);

		private:
			friend class UIObject;
			Constraints();
			~Constraints();
			void UpdateConstraints(UIObject* pUIObject);
			void Update(float& value, BaseUIConstraint* pConstraint, UIObject* pUIObject);

		private:
			BaseUIConstraint* m_pXConstraint;
			BaseUIConstraint* m_pYConstraint;
			BaseUIConstraint* m_pWidthConstraint;
			BaseUIConstraint* m_pHeightConstraint;
		};
	}
}