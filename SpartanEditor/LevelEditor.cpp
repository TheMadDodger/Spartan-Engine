#include "stdafx.h"
#include "LevelEditor.h"
#include "GameObject.h"
#include "Components.h"
#include "ComponentParameters.h"
#include <BaseGame.h>

LevelEditor::LevelEditor() : GameScene("Level Editor")
{
}


LevelEditor::~LevelEditor()
{
}

void LevelEditor::RenderGUI()
{
	CreateObjectList();
	CreateInspector();
}

void LevelEditor::Initialize(const GameContext &gameContext)
{
	/*auto pObj = new GameObject("Parent Object");
	pObj->AddComponent(new ImageRenderComponent("./Resources/TwitchAvatar.png"));
	auto pObj1 = new GameObject("Child Of Parent");
	pObj1->AddComponent(new ImageRenderComponent("./Resources/TwitchAvatar.png"));
	pObj1->GetTransform()->SetScale(Vector2(0.5f, 0.5f));
	pObj->AddChild(pObj1);
	auto pObj2 = new GameObject("Child Of Child");
	pObj2->AddComponent(new ImageRenderComponent("./Resources/TwitchAvatar.png"));
	pObj2->GetTransform()->SetScale(Vector2(0.5f, 0.5f));
	pObj1->AddChild(pObj2);

	pObj1 = new GameObject("Child Of Parent");
	pObj->AddChild(pObj1);
	pObj2 = new GameObject("Child Of Child");
	pObj1->AddChild(pObj2);

	pObj1 = new GameObject("Child Of Parent");
	pObj->AddChild(pObj1);
	pObj2 = new GameObject("Child Of Child");
	pObj1->AddChild(pObj2);

	pObj1 = new GameObject("Child Of Parent");
	pObj->AddChild(pObj1);
	pObj2 = new GameObject("Child Of Child");
	pObj1->AddChild(pObj2);

	pObj1 = new GameObject("Child Of Parent");
	pObj->AddChild(pObj1);
	pObj2 = new GameObject("Child Of Child");
	pObj1->AddChild(pObj2);

	pObj1 = new GameObject("Child Of Parent");
	pObj->AddChild(pObj1);
	pObj2 = new GameObject("Child Of Child");
	pObj1->AddChild(pObj2);

	AddChild(pObj);*/
}

void LevelEditor::Update(const GameContext &)
{
}

void LevelEditor::Draw(const GameContext &)
{
}

void LevelEditor::CreateObjectList()
{
	m_I = 0;

	ImGuiWindowFlags window_flags = 0;
	//window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(300, 680));

	ImGui::Begin("Object List", NULL, window_flags);
	//ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	if (ImGui::IsItemClicked(1))
	{
		m_CurrentRightClickedObject = nullptr;
		ImGui::OpenPopup("object_menu_popup");
	}
	if (ImGui::BeginPopup("object_menu_popup"))
	{
		ObjectMenu();
		ImGui::EndPopup();
	}

	if (ImGui::TreeNode("Scene Objects"))
	{
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3); // Increase spacing to differentiate leaves from expanded contents.
		
		auto children = GetChildren();
		for (auto pChild : children)
		{
			ChildrenList(pChild);
		}
		ImGui::PopStyleVar();
		ImGui::TreePop();
	}
	ImGui::End();
}

void LevelEditor::ChildrenList(GameObject *pChild)
{
	// Disable the default open on single-click behavior and pass in Selected flag according to our selection state.
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (pChild->IsSelected() ? ImGuiTreeNodeFlags_Selected : 0);
	
	auto childrenOfChild = pChild->GetChildren();
	if (!childrenOfChild.empty())
	{
		bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)m_I, node_flags, pChild->GetName());
		if (ImGui::IsItemClicked())
		{
			if(m_CurrentSelectedObject != pChild)
				ComponentParameterManager::GetInstance()->Clear();

			if (m_CurrentSelectedObject)
				m_CurrentSelectedObject->Select(false);
			pChild->Select(true);
			m_CurrentSelectedObject = pChild;
		}
		if (ImGui::IsItemClicked(1))
		{
			m_CurrentRightClickedObject = pChild;
			ImGui::OpenPopup("object_menu_popup" + m_I);
		}
		if (ImGui::BeginPopup("object_menu_popup" + m_I))
		{
			ObjectMenu();
			ImGui::EndPopup();
		}
		++m_I;
		// Node
		if (node_open)
		{
			for (auto pChildOfChild : childrenOfChild)
			{
				ChildrenList(pChildOfChild);
			}

			ImGui::TreePop();
		}
	}
	else
	{
		// Leaf: The only reason we have a TreeNode at all is to allow selection of the leaf. Otherwise we can use BulletText() or TreeAdvanceToLabelPos()+Text().
		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
		ImGui::TreeNodeEx((void*)(intptr_t)m_I, node_flags, pChild->GetName());
		if (ImGui::IsItemClicked())
		{
			if (m_CurrentSelectedObject)
				m_CurrentSelectedObject->Select(false);
			pChild->Select(true);
			m_CurrentSelectedObject = pChild;
		}
		if (ImGui::IsItemClicked(1))
		{
			m_CurrentRightClickedObject = pChild;
			ImGui::OpenPopup("object_menu_popup" + m_I);
		}
		if (ImGui::BeginPopup("object_menu_popup" + m_I))
		{
			ObjectMenu();
			ImGui::EndPopup();
		}
		++m_I;
	}
}

void LevelEditor::CreateInspector()
{
	ImGuiWindowFlags window_flags = 0;
	//window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowPos(ImVec2(1920 - 300, 0));
	ImGui::SetNextWindowSize(ImVec2(300, 680));

	ImGui::Begin("Inspector", NULL, window_flags);
	//ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	if (m_CurrentSelectedObject)
	{
		ImGui::Checkbox("Enabled", &m_CurrentSelectedObject->m_Enabled);
		ImGui::InputText("Name", m_CurrentSelectedObject->GetName(), 200, ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll);

		auto components = m_CurrentSelectedObject->GetComponents();
		int i = 1;
		for (auto pComponent : components)
		{
			auto text = std::to_string(i) + ": " + pComponent->GetName();

			if (ImGui::TreeNode(text.data()))
			{
				auto pParam = ComponentParameterManager::GetInstance()->Create(pComponent);
				if (pParam)
					pParam->LoadParams();

				ImGui::TreePop();
			}
			++i;
		}
	}

	ImGui::End();
}

void LevelEditor::ObjectMenu()
{
	GameObject *pCreatedObj = nullptr;
	ImGui::MenuItem("Object Menu", NULL, false, false);
	if (ImGui::MenuItem("Copy", "Ctrl+C"))
	{

	}
	if (ImGui::MenuItem("Paste", "Ctrl+V"))
	{

	}
	if (ImGui::MenuItem("Duplicate"))
	{

	}
	if (ImGui::MenuItem("Delete"))
	{
		if (m_CurrentRightClickedObject)
		{
			auto pParent = m_CurrentRightClickedObject->GetParent();
			if (pParent)
				pParent->RemoveChild(m_CurrentRightClickedObject, true);
			else
				RemoveChild(m_CurrentRightClickedObject, true);

			if (m_CurrentRightClickedObject == m_CurrentSelectedObject)
				m_CurrentSelectedObject = nullptr;
		}
	}
	if (ImGui::BeginMenu("Create"))
	{
		if (ImGui::MenuItem("Empty"))
		{
			pCreatedObj = new GameObject("Empty Game Object");
			auto pTempComp = pCreatedObj->AddComponent(new ImageRenderComponent());
		}
		if (ImGui::BeginMenu("Geometry"))
		{
			if (ImGui::MenuItem("Box"))
			{

			}
			if (ImGui::MenuItem("Circle"))
			{

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Effects"))
		{
			if (ImGui::MenuItem("Particle Emitter"))
			{

			}
			if (ImGui::MenuItem("Camera"))
			{

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("UI"))
		{
			if (ImGui::MenuItem("UI Container"))
			{

			}
			if (ImGui::MenuItem("UI Button"))
			{

			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (pCreatedObj)
		if (m_CurrentRightClickedObject)
			m_CurrentRightClickedObject->AddChild(pCreatedObj);
		else
			AddChild(pCreatedObj);
}
