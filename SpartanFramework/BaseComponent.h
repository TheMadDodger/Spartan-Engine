#pragma once
#include "stdafx.h"
#include "SerializedObject.h"
#include "SerializedProperty.h"

#define COMPONENT(comp) BASIC_OBJECT(comp, BaseComponent)

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
	class GameObject;

	class BaseComponent : public Serialization::SerializedObject
	{
	public:
		BaseComponent(const char* name = "BaseComponent");
		virtual ~BaseComponent();

		GameObject* GetGameObject() const { return m_pGameObject; }

		//static BaseComponent* CreateFromName(const std::string& name);

		const std::string& GetName() { return m_Name; }

		virtual void CustomEditor() {};

		bool IsInitialized() { return m_bInitialized; }
		bool IsEnabled() { return m_bEnabled; }
		void SetEnabled(bool enabled) { m_bEnabled = enabled; }

		BaseComponent* CreateComponentFromFileStream();

		//static size_t GetRegisteredComponentCount();
		//static BaseComponent* GetRegisteredComponent(int index);

		virtual std::string GetComponentPath();

	protected:
		friend class GameObject;
		virtual void RootAwake();
		virtual void RootInitialize(const GameContext& gameContext);
		virtual void RootUpdate(const GameContext& gameContext);
		virtual void RootDraw(const GameContext& gameContext);

		virtual void Awake() {};
		virtual void Initialize(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };
		virtual void PostInitialize(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };
		virtual void Update(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };
		virtual void Draw(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };
		virtual void OnDestroy() { }

		virtual void DefineSerializedProperties(std::vector<Serialization::SerializedProperty>&) override {};
		bool m_CanTickInEditor = false;
		bool m_CanTickInGame = true;
		bool m_bEnabled = true;
		bool m_bInitialized = false;

	private:
		friend class EditorApp;
		friend class GameObject;
		friend class Spartan::UI::UIObject;
		friend class Spartan::UI::Canvas;
		void SetGameObject(GameObject* pObject);
		GameObject* m_pGameObject = nullptr;

		std::string m_Name;
	};

}