#include "stdafx.h"
#include "Constraints.h"
#include "BaseUIConstraint.h"
#include "UIObject.h"
#include "Canvas.h"
#include "TransformComponent.h"

namespace SpartanEngine
{
	namespace UI
	{
		Constraints::Constraints() : m_pXConstraint(nullptr), m_pYConstraint(nullptr),
			m_pWidthConstraint(nullptr), m_pHeightConstraint(nullptr), m_Enable(true)
		{
		}

		Constraints::~Constraints()
		{
			delete m_pXConstraint;
			m_pXConstraint = nullptr;
			delete m_pYConstraint;
			m_pYConstraint = nullptr;
			delete m_pWidthConstraint;
			m_pWidthConstraint = nullptr;
			delete m_pHeightConstraint;
			m_pHeightConstraint = nullptr;
		}

		void Constraints::SetX(BaseUIConstraint* pConstraint)
		{
			if (m_pXConstraint != nullptr) delete m_pXConstraint;
			m_pXConstraint = pConstraint;
			if (m_pXConstraint != nullptr) m_pXConstraint->SetAxis(BaseUIConstraint::Axis::X);
		}

		void Constraints::SetY(BaseUIConstraint* pConstraint)
		{
			if (m_pYConstraint != nullptr) delete m_pYConstraint;
			m_pYConstraint = pConstraint;
			if (m_pYConstraint != nullptr) m_pYConstraint->SetAxis(BaseUIConstraint::Axis::Y);
		}

		void Constraints::SetWidth(BaseUIConstraint* pConstraint)
		{
			if (m_pWidthConstraint != nullptr) delete m_pWidthConstraint;
			m_pWidthConstraint = pConstraint;
			if (m_pWidthConstraint != nullptr) m_pWidthConstraint->SetAxis(BaseUIConstraint::Axis::X);
		}

		void Constraints::SetHeight(BaseUIConstraint* pConstraint)
		{
			if (m_pHeightConstraint != nullptr) delete m_pHeightConstraint;
			m_pHeightConstraint = pConstraint;
			if (m_pHeightConstraint != nullptr) m_pHeightConstraint->SetAxis(BaseUIConstraint::Axis::Y);
		}

		void Constraints::HeightBeforeWidth(bool enable)
		{
			m_HeightBeforeWidth = enable;
		}

		void Constraints::YBeforeX(bool enable)
		{
			m_YBeforeX = enable;
		}

		void Constraints::SetEnabled(bool enable)
		{
			m_Enable = enable;
		}

		void Constraints::UpdateConstraints(UIObject* pUIObject)
		{
			if (!m_Enable) return;

			if (!m_YBeforeX) Update(pUIObject->GetTransform()->Position.x, m_pXConstraint, pUIObject);
			Update(pUIObject->GetTransform()->Position.y, m_pYConstraint, pUIObject);
			if (m_YBeforeX) Update(pUIObject->GetTransform()->Position.x, m_pXConstraint, pUIObject);
			
			if (!m_HeightBeforeWidth) Update(pUIObject->m_Dimensions.x, m_pWidthConstraint, pUIObject);
			Update(pUIObject->m_Dimensions.y, m_pHeightConstraint, pUIObject);
			if (m_HeightBeforeWidth)Update(pUIObject->m_Dimensions.x, m_pWidthConstraint, pUIObject);
		}

		void Constraints::Update(float& value, BaseUIConstraint* pConstraint, UIObject* pUIObject)
		{
			if (!pConstraint) return;
			pConstraint->UpdateConstraint(pUIObject);
			value = pConstraint->FetchResult();
		}
	}
}