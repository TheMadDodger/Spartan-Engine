#include "stdafx.h"
#include "GameObjectEditor.h"

namespace Spartan::Editor
{
	GameObjectEditor::GameObjectEditor() : m_Initialized(false)
	{
	}

	GameObjectEditor::~GameObjectEditor()
	{
	}

	void GameObjectEditor::OnGUI()
	{
		if (!m_Initialized) Initialize();
		GameObject* pObject = (GameObject*)m_pTarget;

		const char* name = pObject->GetName();
		memcpy(m_NameBuff, name, strlen(name));
		ImGui::InputText("Object Name", m_NameBuff, MAXNAMESIZE);
		pObject->SetName(m_NameBuff);

		std::for_each(m_pComponentEditors.begin(), m_pComponentEditors.end(), [&](Editor* pEditor)
			{
				pEditor->OnGUI();
			});
	}

	void GameObjectEditor::Initialize()
	{
		GameObject* pGameObject = (GameObject*)m_pTarget;
		const vector<BaseComponent*>& pComponents = pGameObject->GetAllComponents();
		std::for_each(pComponents.begin(), pComponents.end(), [&](BaseComponent* pComponent)
			{
				Editor* pEditor = Editor::CreateEditor(pComponent);
				if (pEditor) this->m_pComponentEditors.push_back(pEditor);
			});
		m_Initialized = true;
	}
}