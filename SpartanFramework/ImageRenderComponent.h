#pragma once
#include "UIComponent.h"
#include <string>

namespace Spartan
{
	class ImageRenderComponent : public UIComponent
	{
	public:
		ImageRenderComponent();
		~ImageRenderComponent();

		// Setters
		void SetTexture(TextureData* pTexture);
		void SetColor(const Color& color);

		// Getters
		TextureData* GetTexture();

	private:
		void Update(const GameContext&) override;
		void Draw(const GameContext&) override;

		bool CanRender() override;

		COMPONENT_EDITOR(ImageRenderComponent)

	private:
		TextureData* m_pImage = nullptr;
		Vector4 m_Offsets;
		Color m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	};
}