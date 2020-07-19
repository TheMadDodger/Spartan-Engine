#pragma once
#include "BaseComponent.h"
#include "UIObject.h"

namespace SpartanEngine
{
	namespace UI
	{
		class UIRenderMaterial;
	}

	class UIComponent : public BaseComponent
	{
	public:
		UIComponent(const char* name);
		~UIComponent();

		UI::UIObject* GetGameObject();
		void SetOrigin(const Origin& origin);
		const Origin& GetOrigin();

		void SetCustomMaterial(UI::UIRenderMaterial* pMaterial);

	protected:
		virtual void RootUpdate(const GameContext& gameContext) override;
		virtual void RootDraw(const GameContext& gameContext) override;
		virtual bool CanRender();

	private:
		void Render();

	protected:
		UI::UIRenderMaterial* m_pUIRenderer;
		UI::UIRenderMaterial* m_pCustomMaterial;

	private:
		Matrix4X4 m_UIMatrix;
		Origin m_Origin;
		static GLuint m_UIVertexArrayID;
		static GLuint m_UIVertexBufferID;
		static bool m_DoesVertexBufferExist;
		static int m_InstanceCount;
	};
}