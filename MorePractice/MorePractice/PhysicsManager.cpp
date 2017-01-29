#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(ObjectPool<ColliderComponent>* a_colliderComponents) : m_colliderComponents(a_colliderComponents)
{

}

void PhysicsManager::Update()
{
	unsigned int numColliderComponents = m_colliderComponents->GetCurrentSize();
	for (unsigned int i = 0; i < numColliderComponents; i++) {
		ColliderComponent *pColliderComponent = m_colliderComponents->GetObjectByIndex(i);
		if (pColliderComponent != nullptr) {
			pColliderComponent->ResetOtherCollider();
		}
	}

	//check all colliders against all other colliders. Is there a faster way to do this?? Obviously octrees, space partitioning, etc
	for (unsigned int i = 0; i < numColliderComponents; i++) {
		for (unsigned int j = 0; j < numColliderComponents; j++) {
			//process collisions
			if (i != j) {
				ColliderComponent *pColliderComponentI = m_colliderComponents->GetObjectByIndex(i);
				if (pColliderComponentI != nullptr) {
					ColliderComponent *pColliderComponentJ = m_colliderComponents->GetObjectByIndex(j);
					if (pColliderComponentJ != nullptr) {
						pColliderComponentI->IsCollidingWith(pColliderComponentJ);
					}
				}
			}
		}
	}
}