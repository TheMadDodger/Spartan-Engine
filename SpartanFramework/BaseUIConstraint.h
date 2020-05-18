#pragma once
namespace SpartanEngine
{
	namespace UI
	{
		class UIObject;

		class BaseUIConstraint
		{
		public:
			BaseUIConstraint();
			~BaseUIConstraint();

			void EnableDebug(bool enabled);

		private:
			friend class Constraints;
			virtual void UpdateConstraint(UIObject* pUIObject) = 0;
			float FetchResult();

		protected:
			bool m_DebugEnabled;

			enum class Axis
			{
				X,
				Y,
			};

		private:
			void SetAxis(const Axis& axis);

		protected:
			float m_Result;
			Axis m_Axis;
		};
	}
}