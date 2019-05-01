#pragma once
#include "BaseComponent.h"
class RigidBodyComponent : public BaseComponent
{
public:
	RigidBodyComponent(const b2BodyType &type = b2BodyType::b2_dynamicBody, const Vector2 &bodyPivot = Vector2(0.0f, 0.0f));
	virtual ~RigidBodyComponent();

	b2Body *Getb2Body() { return m_Body; };

protected:
	void Initialize(const GameContext &gameContext) override;
	void Cleanup() override;
	//void Update(const GameContext &gameContext) override;
	//void Draw(const GameContext &gameContext) override;

private:
	virtual BaseComponent *Create() { return new RigidBodyComponent(); }

	b2Body *m_Body = nullptr;
	Vector2 m_BodyPivot;

	b2BodyType m_BodyType;
};

