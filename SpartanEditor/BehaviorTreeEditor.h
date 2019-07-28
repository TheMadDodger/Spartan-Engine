#pragma once
#include "EditorWindow.h"

class BehaviorTreeEditor : public EditorWindowTemplate<BehaviorTreeEditor>
{
public:
	BehaviorTreeEditor();
	virtual ~BehaviorTreeEditor();

private:
	virtual void OnGUI() override;
};

