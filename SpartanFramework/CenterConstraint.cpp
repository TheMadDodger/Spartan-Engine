#include "stdafx.h"
#include "CenterConstraint.h"
#include "UIObject.h"
#include "UICanvas.h"

namespace SpartanEngine
{
	namespace UI
	{
		CenterConstraint::CenterConstraint()
		{
		}

		CenterConstraint::~CenterConstraint()
		{
		}

		void CenterConstraint::UpdateConstraint(UIObject* pUIObject)
		{
			UICanvas* pCanvas = pUIObject->GetParentCanvas();
			//pCanvas->Get
		}
	}
}