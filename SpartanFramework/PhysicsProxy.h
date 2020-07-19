#pragma once
#include "SEObject.h"
#include "ApplicationStructs.h"
#include <btBulletDynamicsCommon.h>

namespace Spartan
{
	class PhysicsProxy : public SEObject
	{
	public:
		PhysicsProxy();
		virtual ~PhysicsProxy();

		void SetGravity(const Vector3& gravityVec);

	private:
		void Initialize();
		void Step(const GameContext& gameContext);

		void AddCollisionObject(btRigidBody* pCollisionObject);
		void RemoveCollisionObject(btRigidBody* pCollisionObject);

	private:
		friend class BaseGame;
		friend class PhysicsObjectComponent;

		btCollisionConfiguration*				m_pCollisionConfig;
		btCollisionDispatcher*					m_pCollisionDispatcher;
		btBroadphaseInterface*					m_pOverlappingPairCache;
		btSequentialImpulseConstraintSolver*	m_pSolver;
		btDiscreteDynamicsWorld*				m_pDynamicsWorld;

		Vector3 m_GravityVector;
	};
}