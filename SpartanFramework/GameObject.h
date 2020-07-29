#pragma once
#include "ApplicationStructs.h"
#include "BaseComponent.h"
#include "SEObject.h"
#include "ISerializable.h"

namespace Spartan
{
	namespace UI
	{
		class UIObject;
		class Canvas;
	}
}

namespace Spartan
{
	class TransformComponent;
	class GameScene;
	struct LayerData;

	class GameObject : public SEObject, ISerializable
	{
	public:
		GameObject(const char* name = "EmptyGameObject", size_t layerID = 0);
		virtual ~GameObject();

		const vector<BaseComponent*>& GetAllComponents() { return m_pComponents; }

		template <typename T>
		vector<T*> GetComponents() const
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

		const vector<BaseComponent*>& GetComponents() const { return m_pComponents; }

		template <typename T>
		T* GetComponent() const
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

		BaseComponent* AddComponent(BaseComponent* pComponentTemplate)
		{
			BaseComponent* pComp = pComponentTemplate->Create();
			pComp->m_pGameObject = this;
			m_pComponents.push_back(pComp);
			pComp->RootAwake();
			return pComp;
		}

		GameScene* GetGameScene() const;
		GameObject* GetChild(size_t index) const;
		const vector<GameObject*>& GetChildren() const;

		GameObject* GetParent() const { return m_pParentObject; }
		void SetParent(GameObject* pParent, bool keepWorldPosition = false);

		const std::string& GetTag() const;
		void SetTag(const std::string& tag);

		bool IsEnabled() const;
		void SetEnabled(bool enabled);

		const char* GetName() const { return m_Name; }

		void SetName(const char* name);

		void Select(bool bSelected) { m_Selected = bSelected; }
		bool IsSelected() const { return m_Selected; }

		const LayerData& GetLayer() const;
		void SetLayer(int layerID);

		bool IsDirty() const;
		void SetDirty();

		virtual const std::type_info& GetBaseType() { return typeid(GameObject); }
		virtual const std::type_info& GetType() { return typeid(GameObject); }

		virtual void Serialize(std::ofstream& fileStream) override;
		virtual void Deserialize(std::ifstream& fileStream) override;

	protected:
		friend class GameScene;
		virtual void RootInitialize(const GameContext& gameContext);
		virtual void RootPostInitialize(const GameContext& gameContext);
		virtual void RootUpdate(const GameContext& gameContext);
		virtual void RootDraw(const GameContext& gameContext);

		virtual void Construct() {};
		virtual void Initialize(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void PostInitialize(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void BeginUpdate(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void Update(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void Draw(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void PostDraw(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); }
		virtual void OnParentUpdated(GameObject* pNewParent) { UNREFERENCED_PARAMETER(pNewParent); }
		virtual void UIHandleMouse(const Vector2& relativeMousePos);
		void PassUIMouseInputToChildren(const Vector2& localMousePos);

		void RootOnEnable();
		void RootOnDisable();

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

		template<class T>
		T* CreateChild()
		{
			T* pChild = new T();
			GameObject* pChildObject = dynamic_cast<GameObject*>(pChild);
			if (pChildObject == nullptr)
				throw new exception("ERROR: Class must be derived from GameObject!!!");

			m_pChildren.push_back(pChild);
			pChildObject->m_pScene = m_pScene;
			pChildObject->m_pParentObject = this;
			return pChild;
		}

		void SetFullDirty();

	private:
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		void SetDirty(bool dirty);
		void SetScene(Spartan::GameScene* pScene);

	private:
		friend class EditorApp;
		friend class GameScene;
		friend class Spartan::UI::UIObject;
		friend class Spartan::UI::Canvas;
		TransformComponent* m_pTransform = nullptr;
		std::vector<BaseComponent*> m_pComponents;
		GameScene* m_pScene = nullptr;
		vector<GameObject*> m_pChildren;
		GameObject* m_pParentObject = nullptr;
		bool m_Persistent = false;
		bool m_bInitialized = false;

		bool m_Enabled = true;
		std::string m_Tag;
		char m_Name[200];
		char m_PrefabName[200] = "";
		size_t m_LayerID;

		bool m_Selected = false;
		bool m_IsDirty;
	};
}