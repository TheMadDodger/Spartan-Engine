#pragma once
#include "BaseComponent.h"

class UIContainer : public BaseComponent
{
public:
	UIContainer(const Vector2 &dimensions);
	virtual ~UIContainer();

	void SetPadding(const Vector2 &padding);
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
	Vector2 m_Dimensions;
	Vector2 m_Padding;

	Color m_Color;

	size_t m_CurrentPage = 0;
	std::vector<GameObject*> m_pUIPages;
};
