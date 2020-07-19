#pragma once
#include "MathHelpers.h"
#include "stdafx.h"
#include "TransformComponent.h"
#include "SEObject.h"
#include "3DColliders.h"

namespace Spartan
{
	class Collider2D : SEObject
	{
	public:
		virtual void DrawDebugShape(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };

	protected:
		virtual b2Shape* ApplyShape() { return nullptr; }

		virtual ~Collider2D()
		{
			if (m_pShape)
			{
				delete m_pShape;
				m_pShape = nullptr;
			}
		};

	protected:
		b2Shape* m_pShape = nullptr;

	private:
		friend class Collider2DComponent;
	};

	class Box2D : public Collider2D
	{
	public:
		Box2D(float width, float hieght) : Dimensions(width, hieght) {};
		Box2D(const Math::Vector2& dimensions) : Dimensions(dimensions) {};

		virtual ~Box2D() {};

		const Math::Vector2 Dimensions;

		void DrawDebugShape(const GameContext& gameContext) override
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
		b2Shape* ApplyShape() override
		{
			m_pShape = new b2PolygonShape();
			static_cast<b2PolygonShape*>(m_pShape)->SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);
			return m_pShape;
		}
	};

	class Circle : public Collider2D
	{
	public:
		Circle(float radius) : m_Radius(radius) {};

		virtual ~Circle() {};

		void DrawDebugShape(const GameContext& gameContext) override
		{
			gameContext.pRenderer->DrawSolidCircle(Vector2::Zero(), m_Radius, Color::Pink());
		}

		void SetRadius(float radius)
		{
			m_Radius = radius;
			m_pShape->m_radius = m_Radius;
		}

	private:
		friend class ColliderComponent;
		b2Shape* ApplyShape() override
		{
			m_pShape = new b2CircleShape();
			m_pShape->m_radius = m_Radius;
			return m_pShape;
		}

	private:
		float m_Radius;
	};
}