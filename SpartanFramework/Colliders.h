#pragma once
#include "MathHelpers.h"
#include "stdafx.h"
#include "TransformComponent.h"

class Collider
{
public:
	virtual void DrawDebugShape(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

protected:
	virtual b2Shape *ApplyShape() { return nullptr; }

	~Collider()
	{
		if (m_pShape)
		{
			delete m_pShape;
			m_pShape = nullptr;
		}
	};

protected:
	b2Shape *m_pShape = nullptr;

private:
	friend class ColliderComponent;
};

class Box : public Collider
{
public:
	Box(float width, float hieght) : Dimensions(width, hieght) {};
	Box(const Math::Vector2 &dimensions) : Dimensions(dimensions) {};

	virtual ~Box() {};

	const Math::Vector2 Dimensions;

	void DrawDebugShape(const GameContext &gameContext) override
	{
		Vector2 topLeft;
		topLeft.x = -Dimensions.x / 2.0f;
		topLeft.y = Dimensions.y / 2.0f;

		Vector2 rightBottom;
		rightBottom.x = Dimensions.x / 2.0f;
		rightBottom.y = -Dimensions.y / 2.0f;

		gameContext.pRenderer->DrawSolidRect(topLeft, rightBottom, Color::Green());
	}

private:
	friend class ColliderComponent;
	b2Shape *ApplyShape() override
	{
		m_pShape = new b2PolygonShape();
		static_cast<b2PolygonShape*>(m_pShape)->SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);
		return m_pShape;
	}
};

class Circle : public Collider
{
public:
	Circle(float radius) : Radius(radius) {};

	virtual ~Circle() {};

	const float Radius;

	void DrawDebugShape(const GameContext &gameContext) override
	{
		gameContext.pRenderer->DrawSolidCircle(Vector2::Zero(), Radius, Color::Pink());
	}

private:
	friend class ColliderComponent;
	b2Shape *ApplyShape() override
	{
		m_pShape = new b2CircleShape();
		return m_pShape;
	}
};
