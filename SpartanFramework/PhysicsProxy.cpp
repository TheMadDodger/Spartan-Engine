#include "stdafx.h"
#include "PhysicsProxy.h"

namespace Spartan
{
	PhysicsProxy::PhysicsProxy() :
		m_pCollisionConfig(nullptr), m_pCollisionDispatcher(nullptr),
		m_pOverlappingPairCache(nullptr), m_pSolver(nullptr), m_pDynamicsWorld(nullptr),
		m_GravityVector(0.0f, -10.0f, 0.0f)
	{
	}

	Spartan::PhysicsProxy::~PhysicsProxy()
	{
		if (m_pCollisionConfig) delete m_pCollisionConfig;
		if (m_pCollisionDispatcher) delete m_pCollisionDispatcher;
		if (m_pOverlappingPairCache) delete m_pOverlappingPairCache;
		if (m_pSolver) delete m_pSolver;
		if (m_pDynamicsWorld) delete m_pDynamicsWorld;

		m_pCollisionConfig = nullptr;
		m_pCollisionDispatcher = nullptr;
		m_pOverlappingPairCache = nullptr;
		m_pSolver = nullptr;
		m_pDynamicsWorld = nullptr;
	}

	void Spartan::PhysicsProxy::SetGravity(const Vector3& gravityVec)
	{
		m_GravityVector = gravityVec;
		if (m_pDynamicsWorld) m_pDynamicsWorld->setGravity(Math::TobtVector3(m_GravityVector));
	}

	void Spartan::PhysicsProxy::Initialize()
	{
		m_pCollisionConfig = new btDefaultCollisionConfiguration();
		m_pCollisionDispatcher = new btCollisionDispatcher(m_pCollisionConfig);
		m_pOverlappingPairCache = new btDbvtBroadphase();
		m_pSolver = new btSequentialImpulseConstraintSolver();
		m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pCollisionDispatcher, m_pOverlappingPairCache, m_pSolver, m_pCollisionConfig);

		m_pDynamicsWorld->setGravity(Math::TobtVector3(m_GravityVector));
	}

	void PhysicsProxy::Step(const GameContext& gameContext)
	{
		float deltaTime = gameContext.pTime->GetDeltaTime() / 1000.0f;
		m_pDynamicsWorld->stepSimulation(deltaTime, 10);
	}

	void PhysicsProxy::AddCollisionObject(btRigidBody* pCollisionObject)
	{
		m_pDynamicsWorld->addRigidBody(pCollisionObject);
	}

	void PhysicsProxy::RemoveCollisionObject(btRigidBody* pCollisionObject)
	{
		m_pDynamicsWorld->removeCollisionObject(pCollisionObject);
	}
}