#include "BulletManager.h"

BulletManager::BulletManager(PhysicsComponent *a_pPhysicsComponents, SpriteComponent *a_pSpriteComponents, ColliderComponent *a_pColliderComponents) :
	m_pPhysicsComponents(a_pPhysicsComponents), m_pSpriteComponents(a_pSpriteComponents), m_pColliderComponents(a_pColliderComponents),
	m_iLastAssignedBullet(-1), m_uiNumActiveBullets(0)
{
	m_bullets = new BulletObject[10];
	for (unsigned int i = 0; i < 10; ++i) {
		m_bullets[i].AddComponent(m_pPhysicsComponents + i);
		m_bullets[i].AddComponent(m_pSpriteComponents + i);
		m_bullets[i].AddComponent(m_pColliderComponents + i);
	}
}

void BulletManager::Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_position) 
{
	//clearly need to make this 10 a const (or a variable if I pass it in, I guess)
	if (m_uiNumActiveBullets < 10) {
		while (true) { //is this bad? My teachers (and I) always taught it was bad coding practice - but otherwise I'm wasting a boolean and an extra check
			++m_iLastAssignedBullet;
			if (m_iLastAssignedBullet >= 10) {
				m_iLastAssignedBullet = 0;
			}
			if (!m_bullets[m_iLastAssignedBullet].IsActive()) {
				m_bullets[m_iLastAssignedBullet].Shoot(a_pOwner, a_iPower, speed, a_fRotationAngle, a_position);
				break;
			}
		}
	}
}

void BulletManager::Update(const double a_dDeltaTime)
{
	m_uiNumActiveBullets = 0; //also don't particularly like this - not sure why
	for (unsigned int i = 0; i < 10; ++i) {
		m_bullets[i].Update(a_dDeltaTime);
		if (m_bullets[i].IsActive()) {
			++m_uiNumActiveBullets;
		}
	}
}