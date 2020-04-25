#pragma once
#include "GameObject.h"

namespace SpartanEngine
{
	namespace UI
	{
		class UICanvas;
		class Constraints;

		class UIObject : public GameObject
		{
		public:
			UIObject(const char* name = "UIObject", size_t layerID = 0);
			~UIObject();

			UICanvas* GetParentCanvas() const;
			void SetSize(float width, float height);

			Constraints* GetConstraints() const;

		protected:
			virtual void OnResize(const Vector2& newDimensions) = 0;

		private:
			void OnParentUpdated(GameObject* pNewParent) override;
			virtual void RootUpdate(const GameContext& gameContext) override;
			virtual void RootDraw(const GameContext& gameContext) override;

		protected:
			UICanvas* m_pParentCanvas;
			Vector2 m_Dimensions;
			Vector2 m_OldDimensions;

		private:
			friend class Constraints;
			Constraints* m_pConstraints;
		};
	}
}