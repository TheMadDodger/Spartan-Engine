#pragma once
#include "EditorWindow.h"
#include <GameObject.h>

namespace Spartan::Editor
{
	class SceneGraphWindow : public EditorWindowTemplate<SceneGraphWindow>
	{
	public:
		SceneGraphWindow();
		virtual ~SceneGraphWindow();

	private:
		virtual void OnGUI() override;

		void ChildrenList(Spartan::GameObject* pChild);
		void ObjectMenu();

	private:
		int m_I;
		GameObject* m_CurrentRightClickedObject;
	};
}