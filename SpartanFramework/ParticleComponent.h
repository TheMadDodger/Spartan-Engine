#pragma once
#include "BaseComponent.h"
class ParticleComponent : public BaseComponent
{
public:
	ParticleComponent();
	virtual ~ParticleComponent();

	EmitterSettings m_Settings;

protected:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;

private:
	COMPONENT_EDITOR(ParticleComponent)

	ParticleSystem *m_pSystem;
	ParticleEmitter *m_pEmitter;
};

