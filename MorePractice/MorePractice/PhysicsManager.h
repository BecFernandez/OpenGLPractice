#pragma once

#include <vector>
#include "Physics.h"
#include "ColliderComponent.h"
#include "ComponentPool.h"

class PhysicsManager
{
public:
	PhysicsManager(ObjectPool<ColliderComponent>* a_colliderComponents);
	void Update();

private:
	ObjectPool<ColliderComponent>* m_colliderComponents;
};