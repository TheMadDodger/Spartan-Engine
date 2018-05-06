#pragma once
#include "../stdafx.h"
#include "BaseGame.h"
#include "Rendering/Renderer.h"
#include "ApplicationStructs.h"
#include "Content/ContentManager.h"
#include "Helpers/MathHelpers.h"

inline Vector2 ToVector2(const b2Vec2 &vec)
{
	return Vector2(vec.x, vec.y);
}

inline b2Vec2 Tob2Vec2(const Vector2 &vec)
{
	return b2Vec2(vec.x, vec.y);
}