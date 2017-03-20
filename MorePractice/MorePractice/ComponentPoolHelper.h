#pragma once
#include "ComponentPool.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"


class ComponentPoolHelper
{
public:
	ComponentPoolHelper();
	~ComponentPoolHelper();
	void Update(double a_fDeltaTime);
	Component* GetComponent(ComponentTypes a_type, unsigned int a_uiComponentID);
	void DestroyComponent(ComponentTypes a_type, unsigned int a_uiComponentID);

	//ok, basically now I'm just putting them in a class so I only have 1 thing to pass instead of 4
	ObjectPool<PhysicsComponent> *m_physicsComponentPool;
	ObjectPool<SpriteComponent> *m_spriteComponentPool;
	ObjectPool<ColliderComponent> *m_colliderComponentPool;
	ObjectPool<HealthComponent> *m_healthComponentPool;
};
