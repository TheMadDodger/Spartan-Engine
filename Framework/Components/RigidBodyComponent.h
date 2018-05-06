#pragma once
#include "BaseComponent.h"
class RigidBodyComponent : public BaseComponent
{
public:
	RigidBodyComponent(const Vector2 &bodyPivot = Vector2(0.0f, 0.0f));
	virtual ~RigidBodyComponent();

	b2Body *Getb2Body() { return m_Body; };

protected:
	void Initialize(const GameContext &gameContext) override;
	//void Update(const GameContext &gameContext) override;
	//void Draw(const GameContext &gameContext) override;

private:
	b2Body *m_Body = nullptr;
	Vector2 m_BodyPivot;
};

