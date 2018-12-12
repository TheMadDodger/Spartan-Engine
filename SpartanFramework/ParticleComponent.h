#pragma once
#include "BaseComponent.h"
class ParticleComponent : public BaseComponent
{
public:
	ParticleComponent(const EmitterSettings &settings);
	virtual ~ParticleComponent();

protected:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;

private:
	virtual BaseComponent *Create() { return new ParticleComponent(EmitterSettings()); }

	EmitterSettings m_Settings;
	ParticleSystem *m_pSystem;
	ParticleEmitter *m_pEmitter;
};

