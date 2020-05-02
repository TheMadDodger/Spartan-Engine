#include "stdafx.h"
#include "UIObject.h"
#include "Canvas.h"
#include "Layers.h"
#include "Constraints.h"
#include "TransformComponent.h"

namespace SpartanEngine
{
	namespace UI
	{
		UIObject::UIObject(const char* name, size_t layerID) : m_pParentCanvas(nullptr), GameObject(name, layerID),
			m_Dimensions(0.0f, 0.0f), m_OldDimensions(m_Dimensions), m_pConstraints(new Constraints())
		{
		}

		UIObject::~UIObject()
		{
			delete m_pConstraints;
			m_pConstraints = nullptr;
		}

		Canvas* UIObject::GetParentCanvas() const
		{
			return m_pParentCanvas;
		}

		void UIObject::SetSize(float width, float height)
		{
			m_Dimensions = Vector2(width, height);
			m_OriginalDimensions = m_Dimensions;
		}

		const Vector2& UIObject::GetSize() const
		{
			return m_Dimensions;
		}

		const Vector2& UIObject::GetOriginalSize() const
		{
			return m_OriginalDimensions;
		}

		Constraints* UIObject::GetConstraints() const
		{
			return m_pConstraints;
		}

		void UIObject::OnParentUpdated(GameObject* pNewParent)
		{
			GameObject* pParent = pNewParent;
			while (pParent != nullptr)
			{
				Canvas* pCanvas = dynamic_cast<Canvas*>(pParent);
				if (pCanvas != nullptr)
				{
					m_pParentCanvas = pCanvas;
					return;
				}
				pParent = pParent->GetParent();
			}
			m_pParentCanvas = nullptr;
			Utilities::Debug::LogWarning("UIObject only works when it is parrented to a UICanvas!\nThis object will not render properly!");
		}

		void UIObject::RootUpdate(const GameContext& gameContext)
		{
			if (!m_bInitialized) // If we haven't initialised yet
			{
				// We initialize
				RootInitialize(gameContext);
			}

			Vector2 lastPosition = GetTransform()->Position.xy();

			m_pConstraints->UpdateConstraints(this);

			if (lastPosition != GetTransform()->Position.xy()) SetDirty();

			if (m_Dimensions != m_OldDimensions)
			{
				OnResize(m_Dimensions);
				m_OldDimensions = m_Dimensions;
				SetDirty();
			}

			for (size_t i = 0; i < m_pComponents.size(); ++i)
			{
				auto pComponent = m_pComponents[i];
				pComponent->RootUpdate(gameContext);
			}

			for (size_t i = 0; i < m_pChildren.size(); ++i)
			{
				auto pChild = m_pChildren[i];
				if (pChild->IsEnabled())
					pChild->RootUpdate(gameContext);
			}

			// User defined Update()
			Update(gameContext);
		}

		void UIObject::RootDraw(const GameContext& gameContext)
		{
			//if (!IsDirty()) return;

			// User defined Draw()
			Draw(gameContext);

			for (auto pComponent : m_pComponents)
			{
				pComponent->RootDraw(gameContext);
			}

			for (auto pChild : m_pChildren)
			{
				if (pChild->IsEnabled())
					pChild->RootDraw(gameContext);
			}

			PostDraw(gameContext);

			SetDirty(false);

			Utilities::Debug::LogInfo("A UIObject was re-rendered!");
		}
	}
}