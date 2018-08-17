#pragma once
enum ValueType
{
	Constant,
	RandomBetweenTwoConstants,
};

enum ChangeType
{
	ConstantValue,
	OverLifeTime,
};

enum AlphaType
{
	Cnst,
	TwoOverLife,
	ThreeOverLife,
};

struct ParticleSettings
{
public:
	// LifeTime
	void ConstantLifeTime(float lifeTime)
	{
		LifeTimeA = lifeTime;
		LifeTimeType = Constant;
	}
	void RandomLifeTimeBetweenTwoConstants(float a, float b)
	{
		LifeTimeType = RandomBetweenTwoConstants;
		LifeTimeA = a;
		LifeTimeB = b;
	}

	// Color
	void SetColor(Color color)
	{
		ColorType = Constant;
		ColorA = color;
	}
	void RandomColorBetween2Constants(Color a, Color b)
	{
		ColorType = RandomBetweenTwoConstants;
		ColorA = a;
		ColorB = b;
	}

	// Color change
	void ColorOverLifeTime(Color endColor)
	{
		DeadColorType = Constant;
		ColorChange = OverLifeTime;
		DeadColorA = endColor;
	}
	void ColorOverLifeTimeBetween2Constants(Color a, Color b)
	{
		DeadColorType = RandomBetweenTwoConstants;
		ColorChange = OverLifeTime;
		DeadColorA = a;
		DeadColorB = b;
	}

	// Direction
	void ConstantDirection(float direction)
	{
		DirectionType = Constant;
		DirectionA = direction;
	}
	void RandomDirectionBetween2Constants(float a, float b)
	{
		DirectionType = RandomBetweenTwoConstants;
		DirectionA = a;
		DirectionB = b;
	}

	// Speed
	void ConstantSpeed(float speed)
	{
		SpeedType = Constant;
		SpeedA = speed;
	}
	void RandomSpeedBetween2Constants(float a, float b)
	{
		SpeedType = RandomBetweenTwoConstants;
		SpeedA = a;
		SpeedB = b;
	}

	// Speed Change
	void SpeedOverLifeTime(float endSpeed)
	{
		SpeedChange = OverLifeTime;
		DeadSpeedType = Constant;
		DeadSpeedA = endSpeed;
	}
	void SpeedOverLifeTimeBetween2Constants(float a, float b)
	{
		SpeedChange = OverLifeTime;
		DeadSpeedType = RandomBetweenTwoConstants;
		DeadSpeedA = a;
		DeadSpeedB = b;
	}

	// Color Change
	void ColorOverLifeTime(float endSpeed)
	{
		SpeedChange = OverLifeTime;
		DeadSpeedA = endSpeed;
	}
	void ColorOverLifeTimeBetween2Constants(float a, float b)
	{
		SpeedType = RandomBetweenTwoConstants;
		SpeedChange = OverLifeTime;
		DeadSpeedA = a;
		DeadSpeedB = b;
	}

	// Alpha Over Lifetime
	void ConstantAlpha(float alpha)
	{
		m_Alpha1 = alpha;
		m_AlphaType = Cnst;
	}
	void AlphaOverLifeTime2(float alpha1, float alpha2)
	{
		m_Alpha1 = alpha1;
		m_Alpha2 = alpha2;
		m_AlphaType = TwoOverLife;
	}
	void AlphaOverLifeTime3(float alpha1, float alpha2, float alpha3)
	{
		m_Alpha1 = alpha1;
		m_Alpha2 = alpha2;
		m_Alpha3 = alpha3;
		m_AlphaType = ThreeOverLife;
	}

	// Rotation
	void SetStartRotation(float rot)
	{
		m_RotationA = rot;
		RotationType = Constant;
	}
	void RandomRotationBetween2Constants(float rotA, float rotB)
	{
		m_RotationA = rotA;
		m_RotationB = rotB;
		RotationType = RandomBetweenTwoConstants;
	}

	// Scale
	void SetStartScale(const Vector2 &scale)
	{
		ScaleA = scale;
		ScaleType = Constant;
		DeadScaleChangeType = ConstantValue;
	}
	void RandomScaleBetweenTwoConstants(const Vector2 &a, const Vector2 &b)
	{
		ScaleA = a;
		ScaleB = b;
		UniformStartScale = false;
		ScaleType = RandomBetweenTwoConstants;
		DeadScaleChangeType = ConstantValue;
	}
	void RandomUniformScaleBetweenTwoConstants(float a, float b)
	{
		ScaleA = Vector2(a, a);
		ScaleB = Vector2(b, b);
		UniformStartScale = true;
		ScaleType = RandomBetweenTwoConstants;
		DeadScaleChangeType = ConstantValue;
	}

	// Scale change
	void ScaleOverLifeTime(const Vector2 &scale)
	{
		DeadScaleA = scale;
		DeadScaleType = Constant;
		DeadScaleChangeType = OverLifeTime;
	}
	void RandomEndScaleBetweenTwoConstants(const Vector2 &a, const Vector2 &b)
	{
		DeadScaleA = a;
		DeadScaleB = b;
		DeadScaleType = RandomBetweenTwoConstants;
		DeadScaleChangeType = OverLifeTime;
	}

	// Angular speed
	void SetAngularSpeed(float spd)
	{
		AngularSpeedA = spd;
		AngularSpeedType = Constant;
		AngularSpeedChangeType = ConstantValue;
	}
	void RandomAngularSpeedBetween2Constants(float a, float b)
	{
		AngularSpeedA = a;
		AngularSpeedB = b;
		AngularSpeedType = RandomBetweenTwoConstants;
		AngularSpeedChangeType = ConstantValue;
	}

	// Angular speed change
	void SetEndAngularSpeed(float spd)
	{
		DeadAngularSpeedA = spd;
		DeadAngularSpeedType = Constant;
		AngularSpeedChangeType = OverLifeTime;
	}
	void RandomEndAngularSpeedBetween2Constants(float a, float b)
	{
		DeadAngularSpeedA = a;
		DeadAngularSpeedB = b;
		DeadAngularSpeedType = RandomBetweenTwoConstants;
		AngularSpeedChangeType = OverLifeTime;
	}

private: // Defined settings
	// LifeTime
	ValueType LifeTimeType = Constant;
	float LifeTimeA = 1.f;
	float LifeTimeB = 1.f;

	// Color
	ValueType ColorType = Constant;
	ChangeType ColorChange = ConstantValue;
	Color ColorA = Color::White();
	Color ColorB = Color::White();
	ValueType DeadColorType = Constant;
	Color DeadColorA = Color::White();
	Color DeadColorB = Color::White();

	// Direction
	ValueType DirectionType = Constant;
	ChangeType DirectionChange = ConstantValue;
	float DirectionA = 0.f;
	float DirectionB = 0.f;
	ValueType DeadDirectionType = Constant;
	float DeadDirectionA = 0.f;
	float DeadDirectionB = 0.f;

	// Speed
	ValueType SpeedType = Constant;
	ChangeType SpeedChange = ConstantValue;
	float SpeedA = 0.f;
	float SpeedB = 0.f;
	ValueType DeadSpeedType = Constant;
	float DeadSpeedA = 0.f;
	float DeadSpeedB = 0.f;

	// Alpha
	float m_Alpha1 = 1.0f;
	float m_Alpha2 = 1.0f;
	float m_Alpha3 = 1.0f;
	AlphaType m_AlphaType = Cnst;

	// Rotation
	float m_RotationA = 0.f;
	float m_RotationB = 0.f;
	ValueType RotationType = Constant;

	// Scale
	Vector2 ScaleA = { 1.0f, 1.0f };
	Vector2 ScaleB = { 1.0f, 1.0f };
	ValueType ScaleType = Constant;
	bool UniformStartScale = false;

	// Scale change
	Vector2 DeadScaleA = { 1.0f, 1.0f };
	Vector2 DeadScaleB = { 1.0f, 1.0f };
	ValueType DeadScaleType = Constant;
	ChangeType DeadScaleChangeType = ConstantValue;
	bool UniformEndScale = false;

	// Size

	// AngularSpeed
	float AngularSpeedA = 0.0f;
	float AngularSpeedB = 0.0f;
	ValueType AngularSpeedType = Constant;

	// AngularSpeed change
	float DeadAngularSpeedA = 0.0f;
	float DeadAngularSpeedB = 0.0f;
	ValueType DeadAngularSpeedType = Constant;
	ChangeType AngularSpeedChangeType = ConstantValue;

	//...

private: // Friend classes
	friend class ParticleEmitter;
	friend class Particle;
};

class ParticleTransform
{
public:
	ParticleTransform() : m_Position(Vector2::Zero()), m_Rotation(Vector3::Zero()), m_Scale(1, 1), m_TransformMatrix(Matrix3X3::CreateIdentityMatrix()) {}
	void BuildTransform(CameraComponent *pCamera);
	void ApplyMatrix();

private:
	friend class Particle;
	Math::Vector2 m_Position;
	Math::Vector3 m_Rotation;
	Math::Vector2 m_Scale;
	Math::Matrix3X3 m_TransformMatrix;
};

class Particle
{
private: // Internal functions
	Particle(const ParticleSettings &settings) : m_Settings(settings) {}
	~Particle() {}

	bool IsDead() { return m_IsDead; }
	void Initialize(const Vector2 &pos);
	void Update(const GameContext &gameContext);
	void Render(const GameContext &gameContext);

private:
	friend class ParticleSystem;
	friend class ParticleEmitter;
	ParticleSettings m_Settings;
	bool m_IsDead = true;

	ParticleTransform m_Transform;

	Math::Vector2 m_StartPosition;
	Math::Vector3 m_StartRotation;
	Math::Vector2 m_StartSize;

	// Life
	float m_CurrentLife = 1.0f;
	float m_LifeTime = 1.0f;
	// Color
	Color m_StartColor;
	Color m_CurrentColor;
	Color m_DeadColor;
	// Direction
	float m_StartDirection;
	float m_CurrentDirection;
	float m_DeadDirection;
	// Speed
	float m_StartSpeed;
	float m_CurrentSpeed;
	float m_DeadSpeed;
	// Alpha
	float m_CurrentAlpha = 1.0f;
	// Rotation
	float m_CurrentRotation = 0.0f;
	// Scale
	Vector2 m_StartScale = {1.0f, 1.0f};
	Vector2 m_CurrentScale = {1.0f, 1.0f};
	Vector2 m_EndScale = {1.0f, 1.0f};
	// Angular speed
	float m_StartAngularSpeed = 0.0f;
	float m_CurrentAngularSpeed = 0.0f;
	float m_EndAngularSpeed = 0.0f;

	ParticleSystem *m_pSystem;
};

struct EmitterSettings
{
	int MaxParticles;
	float SpawnIntervals;
	Vector2 Position;
	ParticleSettings PartSettings;
};

class ParticleEmitter
{
public:
	void UpdateSettings(const EmitterSettings &settings);

private:
	ParticleEmitter(const EmitterSettings &emitterSettings) : m_Settings(emitterSettings), m_pParticles(std::vector<Particle*>()) {}
	~ParticleEmitter();

	void Initialize();
	void Tick(const GameContext &gameContext);
	void Render(const GameContext &gameContext);

private: // Internal functions
	void SpawnParticle();

private:
	friend class ParticleSystem;
	EmitterSettings m_Settings;
	std::vector<Particle*> m_pParticles;
	bool m_Initialized = false;
	Math::Vector2 m_Position;
	float m_Time = 0.0f;

	ParticleSystem *m_pSystem;
};

class ParticleSystem
{
public:
	void Tick(const GameContext &gameContext);
	void Paint(const GameContext &gameContext);
	void EnableDebugRender(bool enable);
	bool IsDebugRenderingEnabled();

	void SetCamera(CameraComponent *pCamera);
	CameraComponent *GetCamera();

	ParticleEmitter *CreateEmitter(const EmitterSettings &emitterSettings);

private:
	ParticleSystem();
	~ParticleSystem();

private:
	friend class ParticleManager;
	std::vector<ParticleEmitter*> m_pEmitters;
	bool m_bDebugRendering = false;

	CameraComponent *m_pCamera;
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