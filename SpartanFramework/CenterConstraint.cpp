#include "stdafx.h"
#include "CenterConstraint.h"
#include "UIObject.h"
#include "Canvas.h"

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
			Canvas* pCanvas = pUIObject->GetParentCanvas();
			//pCanvas->Get
		}
	}
}