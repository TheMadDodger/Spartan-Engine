#pragma once
#include "../Helpers/MathHelpers.h"
#include "../../stdafx.h"

class Collider
{
protected:
	virtual void ApplyShape(b2PolygonShape *pPolygonShape) { UNREFERENCED_PARAMETER(pPolygonShape); };

private:
	friend class ColliderComponent;
};

class Box : public Collider
{
public:
	Box(float width, float hieght) : Dimensions(width, hieght) {};
	Box(const Math::Vector2 &dimensions) : Dimensions(dimensions) {};

	const Math::Vector2 Dimensions;

private:
	friend class ColliderComponent;
	void ApplyShape(b2PolygonShape *pPolygonShape) override
	{
		pPolygonShape->SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);
	}
};

class Circle : public Collider
{
public:
	Circle(float radius) : Radius(radius) {};

	const float Radius;

private:
	friend class ColliderComponent;
	void ApplyShape(b2PolygonShape *pPolygonShape) override
	{
		UNREFERENCED_PARAMETER(pPolygonShape);
		//pPolygonShape->Set()
	}
};