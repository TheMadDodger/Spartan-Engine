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

		pEmitter->Tick(gameContext);
	}
}

void ParticleSystem::Paint(const GameContext &gameContext)
{
	for (auto pPart : m_pEmitters)
	{
		pPart->Render(gameContext);
	}
}

void ParticleSystem::EnableDebugRender(bool enable)
{
	m_bDebugRendering = enable;
}

bool ParticleSystem::IsDebugRenderingEnabled()
{
	return m_bDebugRendering;
}

ParticleEmitter *ParticleSystem::CreateEmitter(const EmitterSettings &emitterSettings)
{
	auto pEmitter = new ParticleEmitter(emitterSettings);
	pEmitter->m_pSystem = this;
	m_pEmitters.push_back(pEmitter);
	return pEmitter;
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
	for (size_t i = 0; i < m_pParticles.size(); ++i)
	{
		m_pParticles[i] = new Particle(m_Settings.PartSettings);
		m_pParticles[i]->m_pSystem = m_pSystem;
	}
	m_Initialized = true;
}

void ParticleEmitter::Tick(const GameContext &gameContext)
{
	for (auto pPart : m_pParticles)
	{
		if (!pPart->IsDead())
		{
			pPart->Update(gameContext);
		}
	}
	if (m_Time >= 1.0f / m_Settings.SpawnIntervals)
	{
		SpawnParticle();
		m_Time -= 1.0f / m_Settings.SpawnIntervals;
	}
	else
	{
		m_Time += gameContext.pTime->GetDeltaTime();
	}
}

void ParticleEmitter::Render(const GameContext &gameContext)
{
	for (auto pPart : m_pParticles)
	{
		if(!pPart->IsDead())
			pPart->Render(gameContext);
	}
}

void ParticleEmitter::SpawnParticle()
{
	// Find a free slot in the particle array
	for (auto pPart : m_pParticles)
	{
		if (pPart->IsDead())
		{
			pPart->Initialize(m_Settings.Position);
			return;
		}
	}
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
	for (auto pPart : m_pSystems)
	{
		pPart->Paint(gameContext);
	}
}

void Particle::Initialize(const Vector2 &pos)
{
	// Transform
	m_Transform.m_Position = pos;
	m_Transform.m_Rotation = Vector3::Zero();
	m_Transform.m_Scale = Vector2(1.f, 1.f);

	/// Setup values
	// LifeTime
	switch (m_Settings.LifeTimeType)
	{
	case Constant:
		m_LifeTime = m_Settings.LifeTimeA;
		break;

	case RandomBetweenTwoConstants:
		m_LifeTime = RandomRange<float>(m_Settings.LifeTimeA, m_Settings.LifeTimeB);
		break;
	}
	m_CurrentLife = m_LifeTime;

	// Color
	switch (m_Settings.ColorType)
	{
	case Constant:
		m_StartColor = m_Settings.ColorA;
		break;

	case RandomBetweenTwoConstants:
		m_StartColor = RandomRange<Color>(m_Settings.ColorA, m_Settings.ColorB);
		break;
	}
	m_CurrentColor = m_StartColor;

	// Alpha
	m_CurrentAlpha = m_Settings.m_Alpha1;

	// Color Change
	switch (m_Settings.DeadColorType)
	{
	case Constant:
		m_DeadColor = m_Settings.DeadColorA;
		break;

	case RandomBetweenTwoConstants:
		m_DeadColor = RandomRange<Color>(m_Settings.DeadColorA, m_Settings.DeadColorB);
		break;
	}

	// Speed
	switch (m_Settings.SpeedType)
	{
	case Constant:
		m_StartSpeed = m_Settings.SpeedA;
		break;

	case RandomBetweenTwoConstants:
		m_StartSpeed = RandomRange<float>(m_Settings.SpeedA, m_Settings.SpeedB);
		break;
	}
	m_CurrentSpeed = m_StartSpeed;

	// Speed Change
	switch (m_Settings.DeadSpeedType)
	{
	case Constant:
		m_DeadSpeed = m_Settings.DeadSpeedA;
		break;

	case RandomBetweenTwoConstants:
		m_DeadSpeed = RandomRange<float>(m_Settings.DeadSpeedA, m_Settings.DeadSpeedB);
		break;
	}

	// Direction
	switch (m_Settings.SpeedType)
	{
	case Constant:
		m_StartDirection = m_Settings.DirectionA;
		break;

	case RandomBetweenTwoConstants:
		m_StartDirection = RandomRange<float>(m_Settings.DirectionA, m_Settings.DirectionB);
		break;
	}
	m_CurrentDirection = m_StartDirection;

	// Direction Change
	switch (m_Settings.DeadSpeedType)
	{
	case Constant:
		m_DeadDirection = m_Settings.DeadDirectionA;
		break;

	case RandomBetweenTwoConstants:
		m_DeadDirection = RandomRange<float>(m_Settings.DeadDirectionA, m_Settings.DeadDirectionB);
		break;
	}

	// Rotation
	switch (m_Settings.RotationType)
	{
	case Constant:
		m_CurrentRotation = m_Settings.m_RotationA;
		break;
	case RandomBetweenTwoConstants:
		m_CurrentRotation = RandomRange<float>(m_Settings.m_RotationA, m_Settings.m_RotationB);
		break;
	}

	// Set alive
	m_IsDead = false;
}

void Particle::Update(const GameContext &gameContext)
{
	/// Update values
	// Update position
	m_Transform.m_Position += LengthDir(m_CurrentSpeed, m_CurrentDirection) * gameContext.pTime->GetDeltaTime() / 1000.0f;
	
	// Update Rotation
	m_Transform.m_Rotation = Vector3(0.f, 0.f, m_CurrentRotation);

	// Update Scale
	m_Transform.m_Scale = Vector2(5.0f, 5.0f);

	// Update Life
	m_CurrentLife -= gameContext.pTime->GetDeltaTime() / 1000.0f;

	// Lifetime factor
	auto lifeFactor = 1 - (m_CurrentLife / m_LifeTime);

	if (m_CurrentLife <= 0.0f)
	{
		m_IsDead = true;
		return;
	}

	/// Update other factors
	// Speed
	switch (m_Settings.SpeedChange)
	{
	case OverLifeTime:
	{
		m_CurrentSpeed = Lerp(m_StartSpeed, m_DeadSpeed, lifeFactor);
	}
	default:
		// Do nothing
		break;
	}

	// Alpha
	switch (m_Settings.m_AlphaType)
	{
	case Cnst:
		m_CurrentAlpha = m_Settings.m_Alpha1;
		break;

	case TwoOverLife:
		m_CurrentAlpha = Math::Lerp(m_Settings.m_Alpha1, m_Settings.m_Alpha2, lifeFactor);
		break;

	case ThreeOverLife:
		if (lifeFactor < 0.5f)
			m_CurrentAlpha = Math::Lerp(m_Settings.m_Alpha1, m_Settings.m_Alpha2, lifeFactor * 2.0f);
		else
			m_CurrentAlpha = Math::Lerp(m_Settings.m_Alpha2, m_Settings.m_Alpha3, (lifeFactor - 0.5f) * 2.0f);
		break;
	}

	// Color
	switch (m_Settings.ColorChange)
	{
	case OverLifeTime:
	{
		m_CurrentColor = Color::Lerp(m_StartColor, m_DeadColor, lifeFactor);
	}
	default:
		// Do nothing
		break;
	}
	// Scale with current alpha
	m_CurrentColor.a = m_CurrentAlpha;

	// Direction
	switch (m_Settings.DirectionChange)
	{
	case OverLifeTime:
	{
		m_CurrentDirection = Lerp(m_StartDirection, m_DeadDirection, lifeFactor);
	}
	default:
		// Do nothing
		break;
	}
}

void Particle::Render(const GameContext &gameContext)
{
	//gameContext.pRenderer->DrawLine(m_Transform.m_Position, m_Transform.m_Position + Vector2::Forward() * 20.f, Color::Green());
	//gameContext.pRenderer->DrawLine(m_Transform.m_Position, m_Transform.m_Position + Vector2::Right() * 20.f, Color::Red());

	m_Transform.BuildTransform();
	glPushMatrix();
	m_Transform.ApplyMatrix();
	gameContext.pRenderer->DrawQuadColorTexture(Vector2(-1.0f, -1.0f), Vector2(1.0f, 1.0f), m_CurrentColor, nullptr);
	if (m_pSystem->IsDebugRenderingEnabled())
	{
		gameContext.pRenderer->DrawLine(Vector2::Zero(), Vector2::Forward() * 2.f, Color::Green());
		gameContext.pRenderer->DrawLine(Vector2::Zero(), Vector2::Right() * 2.f, Color::Red());
	}
	glPopMatrix();
}

void ParticleTransform::BuildTransform()
{
	m_TransformMatrix = Matrix3X3::CreateScaleRotationTranslationMatrix(m_Position, m_Rotation, m_Scale);
}

void ParticleTransform::ApplyMatrix()
{
	/// Applies the transform to OpenGL so everything rendered after it uses its transform
	// Extraxt all data from the Transform matrix
	Vector2 pos = m_TransformMatrix.ExtraxtTranslation();
	Vector2 scale = m_TransformMatrix.ExtraxtScale();
	Vector3 rot = m_TransformMatrix.ExtraxtRotation();

	// Convert rotation to Radians since OpenGL needs Radians
	rot.z = rot.z / M_PI * 180.0f;

	// Apply Transform to OpenGL
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(rot.z, 0, 0, 1);
	glScalef(scale.x, scale.y, 1);
}
