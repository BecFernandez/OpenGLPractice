#pragma once
#include "BulletObject.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

class BulletManager
{
public:
	BulletManager(PhysicsComponent *a_pPhysicsComponents, SpriteComponent *a_pSpriteComponents, ColliderComponent *a_pColliderComponents);
	void Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_position);
	void Update(const double a_dDeltaTime);
private:
	SpriteComponent *m_pSpriteComponents;
	PhysicsComponent *m_pPhysicsComponents;
	ColliderComponent *m_pColliderComponents;

	int m_iLastAssignedBullet;
	unsigned int m_uiNumActiveBullets;
	BulletObject* m_bullets;
};