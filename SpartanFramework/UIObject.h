#pragma once
#include "GameObject.h"

namespace SpartanEngine
{
	namespace UI
	{
		class Canvas;
		class Constraints;

		class UIObject : public GameObject
		{
		public:
			UIObject(const char* name = "UIObject", size_t layerID = 0);
			~UIObject();

			Canvas* GetParentCanvas() const;
			void SetSize(float width, float height);
			void SetOriginalSize(float width, float height);
			const Vector2 &GetSize() const;
			const Vector2 &GetOriginalSize() const;

			Constraints* GetConstraints() const;

		protected:
			virtual void OnResize(const Vector2&) {};

		private:
			void OnParentUpdated(GameObject* pNewParent) override;
			virtual void RootUpdate(const GameContext& gameContext) override;
			virtual void RootDraw(const GameContext& gameContext) override;

		protected:
			Canvas* m_pParentCanvas;
			Vector2 m_OriginalDimensions;
			Vector2 m_Dimensions;
			Vector2 m_OldDimensions;

		private:
			friend class Constraints;
			Constraints* m_pConstraints;
		};
	}
}