#pragma once
#include "BaseComponent.h"

class UIContainer : public BaseComponent
{
public:
	UIContainer(const Vector2 &dimensions);
	virtual ~UIContainer();

	void SetPadding(const Vector2 &padding);
	void SetDimensions(const Vector2 &dimensions);
	void SetColor(const Color &color);
	const Vector2 &GetDimensions() { return m_Dimensions; }
	const Vector2 &GetPadding() { return m_Padding; }

	void AddPage(GameObject *pPage);
	void SetPage(size_t pageID);

private:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

private:
	virtual BaseComponent *Create() { return new UIContainer(Vector2(20.f, 20.f)); }

	Vector2 m_Dimensions;
	Vector2 m_Padding;

	Color m_Color;

	size_t m_CurrentPage = 0;
	std::vector<GameObject*> m_pUIPages;
};
