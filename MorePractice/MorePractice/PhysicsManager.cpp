#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(ComponentPoolHelper *a_pComponentPoolHelper) : m_pComponentPoolHelper(a_pComponentPoolHelper)
{

}

void PhysicsManager::Update()
{
	unsigned short numColliderComponents = m_pComponentPoolHelper->m_colliderComponentPool->GetCurrentSize();
	for (unsigned short i = 0; i < numColliderComponents; i++) {
		ColliderComponent *pColliderComponent = (ColliderComponent*)m_pComponentPoolHelper->m_colliderComponentPool->GetObjectByIndex(i);
		if (pColliderComponent != nullptr) {
			pColliderComponent->ResetOtherCollider();
		}
	}

	//check all colliders against all other colliders. Is there a faster way to do this?? Obviously octrees, space partitioning, etc
	for (unsigned short i = 0; i < numColliderComponents; i++) {
		for (unsigned short j = 0; j < numColliderComponents; j++) {
			//process collisions
			if (i != j) {
				ColliderComponent *pColliderComponentI = (ColliderComponent*)m_pComponentPoolHelper->m_colliderComponentPool->GetObjectByIndex(i);
				if (pColliderComponentI != nullptr) {
					ColliderComponent *pColliderComponentJ = (ColliderComponent*)m_pComponentPoolHelper->m_colliderComponentPool->GetObjectByIndex(j);
					if (pColliderComponentJ != nullptr) {
						pColliderComponentI->IsCollidingWith(pColliderComponentJ);
					}
				}
			}
		}
	}
}