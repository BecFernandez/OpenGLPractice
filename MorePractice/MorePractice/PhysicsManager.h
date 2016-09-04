#pragma once

#include <vector>
#include "Physics.h"
#include "ColliderComponent.h"

class PhysicsManager
{
public:
	void AddCollider(ColliderComponent* a_pColliderComponent);
	void Update();

private:
	std::vector<ColliderComponent*> m_colliders;
};