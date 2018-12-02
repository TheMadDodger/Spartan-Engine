#pragma once
#include "BaseComponent.h"
class UIComponent : public BaseComponent
{
public:
	UIComponent();
	~UIComponent();

private:
	virtual BaseComponent *Create() { return new UIComponent(); }
};

