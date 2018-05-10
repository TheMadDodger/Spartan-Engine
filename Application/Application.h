#pragma once
const int Box2DVelocityIterations = 6; // How many velocity iterations should Box2D per game tick perform?
const int Box2DPositionIterations = 2; // How many position iterations should Box2D per game tick perform?
const int FixedUpdateSpeed = 60; // Used for Box2D ticks
const Math::Color PhysicsBoxDebugColor = Math::Color::Green(); // This color will be used to render physics debug boxes
const Math::Color PhysicsCircleDebugColor = Math::Color::Pink(); // This color will be used to render physics debug circles
const Math::Color PhysicsOtherDebugColor = Math::Color::Pink(); // This color will be used to render other physics debug shapes