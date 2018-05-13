#include "stdafx.h"
#include "../../stdafx.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
	for (auto pEmitter : m_pEmitters)
	{
		delete pEmitter;
	}
	m_pEmitters.clear();
}

void ParticleSystem::Tick(const GameContext &gameContext)
{
	for (auto pEmitter : m_pEmitters)
	{
		if (!pEmitter->m_Initialized)
			pEmitter->Initialize();

		pEmitter->Tick();
	}
}

ParticleEmitter *ParticleSystem::CreateEmitter(const EmitterSettings &emitterSettings)
{
	m_pEmitters.push_back(new ParticleEmitter(emitterSettings));
	return m_pEmitters[m_pEmitters.size() - 1];
}

ParticleEmitter::~ParticleEmitter()
{
	for (auto pPart : m_pParticles)
	{
		if (pPart)
		{
			delete pPart;
			pPart = nullptr;
		}
	}
	m_pParticles.clear();
}

void ParticleEmitter::Initialize()
{
	m_pParticles.resize(m_Settings.MaxParticles);
	m_Initialized = true;
}

void ParticleEmitter::Tick(const GameContext &gameContext)
{
}

void ParticleEmitter::Render(const GameContext & gameContext)
{
}

ParticleManager::~ParticleManager()
{
	for (auto pPart : m_pSystems)
	{
		delete pPart;
	}
	m_pSystems.clear();
}

ParticleSystem *ParticleManager::CreateParticleSystem()
{
	m_pSystems.push_back(new ParticleSystem());
	return m_pSystems[m_pSystems.size() - 1];
}

void ParticleManager::Tick(const GameContext &gameContext)
{
	// Tick all systems
	for (auto pPart : m_pSystems)
	{
		pPart->Tick(gameContext);
	}
}

void ParticleManager::Paint(const GameContext &gameContext)
{
}
