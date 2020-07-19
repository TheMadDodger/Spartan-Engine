#pragma once
#include "BaseComponent.h"

namespace Spartan
{
	namespace UI
	{
		class UIContainer : public BaseComponent
		{
		public:
			UIContainer();
			virtual ~UIContainer();

			void SetPadding(const Vector2& padding);
			void SetDimensions(const Vector2& dimensions);
			void SetColor(const Color& color);
			const Vector2& GetDimensions() { return m_Dimensions; }
			const Vector2& GetPadding() { return m_Padding; }

			void AddPage(GameObject* pPage);
			void SetPage(size_t pageID);
			GameObject* GetActivePage();

		private:
			void Initialize(const GameContext& gameContext) override;
			void Update(const GameContext& gameContext) override;
			void Draw(const GameContext& gameContext) override;

		private:
			COMPONENT_EDITOR(UIContainer)

				Vector2 m_Dimensions;
			Vector2 m_Padding;

			Color m_Color;

			size_t m_CurrentPage = 0;
			std::vector<GameObject*> m_pUIPages;
		};
	}
}