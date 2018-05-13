#pragma once

struct ParticleSettings
{
private:
	friend class ParticleEmitter;
	Math::Vector2 StartPosition;
	Math::Vector2 StartRotation;
	Math::Vector2 StartSize;
};

class ParticleTransform
{
private:
	friend class Particle;
	Math::Vector2 m_Position;
	Math::Vector3 m_Rotation;
	Math::Vector2 m_Scale;
	Math::Matrix3X3 m_TransformMatrix;
};

class Particle
{
private:
	Particle(const ParticleSettings &settings) : m_Settings(settings) {}
	~Particle() {}

private:
	friend class ParticleSystem;
	friend class ParticleEmitter;
	ParticleSettings m_Settings;
	bool m_IsDead = false;

	ParticleTransform m_Transform;
};

struct EmitterSettings
{
	int MaxParticles;
	float SpawnIntervals;
};

class ParticleEmitter
{
private:
	ParticleEmitter(const EmitterSettings &emitterSettings) : m_Settings(emitterSettings), m_pParticles(std::vector<Particle*>()) {}
	~ParticleEmitter();

	void Initialize();
	void Tick(const GameContext &gameContext);
	void Render(const GameContext &gameContext);

private:
	friend class ParticleSystem;
	EmitterSettings m_Settings;
	std::vector<Particle*> m_pParticles;
	bool m_Initialized = false;
	Math::Vector2 m_Position;
};

class ParticleSystem
{
public:
	void Tick(const GameContext &gameContext);
	void Paint(const GameContext &gameContext);

	ParticleEmitter *CreateEmitter(const EmitterSettings &emitterSettings);

private:
	ParticleSystem();
	~ParticleSystem();

private:
	friend class ParticleManager;
	std::vector<ParticleEmitter*> m_pEmitters;
};

class ParticleManager
{
public:
	ParticleManager() {};
	~ParticleManager();
public:
	ParticleSystem *CreateParticleSystem();

	void Tick(const GameContext &gameContext);
	void Paint(const GameContext &gameContext);

private:
	std::vector<ParticleSystem*> m_pSystems;
};