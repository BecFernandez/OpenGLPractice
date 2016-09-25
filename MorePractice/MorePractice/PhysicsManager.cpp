#include "PhysicsManager.h"

void PhysicsManager::AddCollider(ColliderComponent* a_pColliderComponent) {
	m_colliders.push_back(a_pColliderComponent);
}

void PhysicsManager::Update()
{
	for (int i = 0; i < m_colliders.size(); i++) {
		m_colliders[i]->ResetOtherCollider();
	}

	//check all colliders against all other colliders. Is there a faster way to do this?? Obviously octrees, space partitioning, etc
	for (unsigned int i = 0; i < m_colliders.size(); i++) {
		for (unsigned int j = 0; j < m_colliders.size(); j++) {
			//process collisions
			if (i != j) {
				m_colliders[i]->IsCollidingWith(m_colliders[j]);
			}
		}
	}
}