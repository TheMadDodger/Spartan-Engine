#pragma once
#include <BaseComponent.h>

class SkeletonEditorComponent : public BaseComponent
{
public:
	SkeletonEditorComponent();
	virtual ~SkeletonEditorComponent();

	COMPONENT_EDITOR(SkeletonEditorComponent)

private:
	virtual void CustomEditor() override;
};

