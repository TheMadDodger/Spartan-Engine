#pragma once
const int Box2DVelocityIterations = 6; // How many velocity iterations should Box2D per game tick perform?
const int Box2DPositionIterations = 2; // How many position iterations should Box2D per game tick perform?
const int FixedUpdateSpeed = 60; // Used for Box2D ticks and for FixedUpdate() method of objects and components