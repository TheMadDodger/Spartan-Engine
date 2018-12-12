#pragma once
#include "stdafx.h"
#include "BaseGame.h"
#include "Renderer.h"
#include "ApplicationStructs.h"
#include "ContentManager.h"
#include "MathHelpers.h"
#include "ParticleSystem.h"

inline Vector2 ToVector2(const b2Vec2 &vec)
{
	return Vector2(vec.x, vec.y);
}

inline b2Vec2 Tob2Vec2(const Vector2 &vec)
{
	return b2Vec2(vec.x, vec.y);
}