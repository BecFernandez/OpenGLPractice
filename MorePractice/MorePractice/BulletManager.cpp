#include "BulletManager.h"

BulletManager::BulletManager(ObjectPool<PhysicsComponent> *a_pPhysicsComponentPool, ObjectPool<SpriteComponent> *a_pSpriteComponentPool, ObjectPool<ColliderComponent> *a_pColliderComponentPool,
	GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader) :
	m_pPhysicsComponentPool(a_pPhysicsComponentPool), m_pSpriteComponentPool(a_pSpriteComponentPool), m_pColliderComponentPool(a_pColliderComponentPool),
	m_iLastAssignedBullet(-1), m_uiNumActiveBullets(0), m_uiVAO(a_uiVAO), m_uiVBO(a_uiVBO), m_uiIBO(a_uiIBO), m_pShader(a_pShader)
{
	m_bulletPool = new ObjectPool<BulletObject>(10);//new BulletObject[10];
}

void BulletManager::Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_position) 
{
	unsigned int bulletID = m_bulletPool->Create(m_pPhysicsComponentPool, m_pSpriteComponentPool, m_pColliderComponentPool, a_pOwner, a_iPower, speed, a_fRotationAngle, a_position,
		m_uiVAO, m_uiVBO, m_uiIBO, m_pShader);
	BulletObject* bullet = m_bulletPool->GetObjectByIndex(bulletID);
	if (bullet != nullptr) {
		bullet->AddObserver(this);
		bullet->Shoot(a_pOwner, a_iPower, speed, a_fRotationAngle, a_position);
	}

}

void BulletManager::Update(const double a_dDeltaTime)
{
	for (unsigned int i = 0; i < m_bulletsToRemove.size(); i++) {
		m_bulletsToRemove[i]->Disable();
		m_bulletPool->Destroy(m_bulletsToRemove[i]->GetID());
	}
	m_bulletsToRemove.clear();
	m_bulletPool->Update(a_dDeltaTime);
}

void BulletManager::OnNotify(Subject *subject)
{
	BulletObject* bulletToRemove = dynamic_cast<BulletObject*>(subject);
	if (bulletToRemove != nullptr) {
		bulletToRemove->RemoveObserver(this);
		m_bulletsToRemove.push_back(bulletToRemove);
	}
}