#pragma once
#include "ApplicationStructs.h"
#include "BaseComponent.h"
#include "SEObject.h"

namespace SpartanEngine
{
	namespace UI
	{
		class UIObject;
		class Canvas;
	}
}

namespace SpartanEngine
{
	class TransformComponent;
	class GameScene;
	struct LayerData;

	class GameObject : public SEObject
	{
	public:
		GameObject(const char* name = "EmptyGameObject", size_t layerID = 0);
		virtual ~GameObject();

		const vector<BaseComponent*>& GetAllComponents() { return m_pComponents; }

		template <typename T>
		vector<T*> GetComponents()
		{
			vector<BaseComponent*> pComponents;
			for (auto pComponent : m_pComponents)
			{
				if (typeid(pComponent) == typeid(T))
				{
					pComponents.push_back(pComponent);
				}
			}
			return pComponents;
		}

		vector<BaseComponent*>& GetComponents() { return m_pComponents; }

		template <typename T>
		T* GetComponent()
		{
			for (auto pComponent : m_pComponents)
			{
				T* pComp = dynamic_cast<T*>(pComponent);
				if (pComp != nullptr)
				{
					return pComp;
				}
			}

			return nullptr;
		}

		TransformComponent* GetTransform() const { return m_pTransform; }
		//BaseComponent *AddComponent(BaseComponent *pComponent);

		template <typename T>
		T* CreateRuntimeComponent()
		{
			T* pT = new T();
			BaseComponent* pComponent = dynamic_cast<BaseComponent*>(pT);
			if (pComponent == nullptr)
			{
				Utilities::Debug::LogError("Can not create component because it does not derive from BaseComponent!");
				return nullptr;
			}
			pComponent->m_pGameObject = this;
			m_pComponents.push_back(pComponent);
			pComponent->RootAwake();
			return pT;
		}

		GameScene* GetGameScene() const;
		GameObject* GetChild(size_t index);
		const vector<GameObject*>& GetChildren();

		GameObject* GetParent() { return m_pParentObject; }
		void SetParent(GameObject* pParent);

		const std::string& GetTag();
		void SetTag(const std::string& tag);

		bool IsEnabled();
		void SetEnabled(bool enabled);

		char* GetName() { return m_Name; }

		void SetName(const char* name);

		void Select(bool bSelected) { m_Selected = bSelected; }
		bool IsSelected() { return m_Selected; }

		const LayerData& GetLayer() const;
		void SetLayer(int layerID);

		bool IsDirty();
		void SetDirty();

	protected:
		friend class GameScene;
		virtual void RootInitialize(const GameContext& gameContext);
		virtual void RootPostInitialize(const GameContext& gameContext);
		virtual void RootUpdate(const GameContext& gameContext);
		virtual void RootDraw(const GameContext& gameContext);

		virtual void Construct() {};
		virtual void Initialize(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void PostInitialize(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void Update(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void Draw(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void PostDraw(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void OnParentUpdated(GameObject* pNewParent) { UNREFERENCED_PARAMETER(pNewParent); }
		virtual void UIHandleMouse(const Vector2& relativeMousePos);
		void PassUIMouseInputToChildren(const Vector2& localMousePos);

		virtual void OnDestroy() {};
		virtual void OnCreated() {};
		virtual void OnEnable() {};
		virtual void OnDisable() {};

		template<class T>
		T* CreateDefaultComponent()
		{
			T* pComp = new T();
			BaseComponent* pComponent = dynamic_cast<BaseComponent*>(pComp);
			if (pComponent == nullptr)
				throw new exception("ERROR: Class must be derived from BaseComponent!!!");

			pComponent->m_pGameObject = this;
			m_pComponents.push_back(pComponent);
			pComponent->SetGameObject(this);
			pComponent->RootAwake();
			return pComp;
		}

		void SetFullDirty();

	private:
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		void SetDirty(bool dirty);

	private:
		friend class LevelEditor;
		friend class GameScene;
		friend class SpartanEngine::UI::UIObject;
		friend class SpartanEngine::UI::Canvas;
		TransformComponent* m_pTransform = nullptr;
		std::vector<BaseComponent*> m_pComponents;
		GameScene* m_pScene = nullptr;
		vector<GameObject*> m_pChildren;
		GameObject* m_pParentObject = nullptr;
		bool m_bInitialized = false;
		bool m_Enabled = true;
		std::string m_Tag;

		bool m_Persistent = false;

		char m_Name[200];
		char m_PrefabName[200] = "";
		bool m_Selected = false;
		size_t m_LayerID;
		bool m_IsDirty;
	};
}