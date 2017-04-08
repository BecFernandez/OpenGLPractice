#include "BulletManager.h"

BulletManager::BulletManager(ComponentPoolHelper *a_pComponentPoolHelper,
	GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader) :
	m_pComponentPoolHelper(a_pComponentPoolHelper),
	m_iLastAssignedBullet(-1), m_uiNumActiveBullets(0), m_uiVAO(a_uiVAO), m_uiVBO(a_uiVBO), m_uiIBO(a_uiIBO), m_pShader(a_pShader)
{
	m_bulletPool = new ObjectPool<BulletObject>(10);//new BulletObject[10];
}

void BulletManager::Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_position) 
{
	unsigned int bulletID = m_bulletPool->Create(m_pComponentPoolHelper, a_pOwner, a_iPower, speed, a_fRotationAngle, a_position,
		m_uiVAO, m_uiVBO, m_uiIBO, m_pShader);
	BulletObject* bullet = m_bulletPool->GetObjectById(bulletID);
	if (bullet != nullptr) {
		bullet->AddObserver(this);
		bullet->Shoot(a_pOwner, a_iPower, speed, a_fRotationAngle, a_position);
	}

}

void BulletManager::Update(const double a_dDeltaTime)
{
	for (unsigned int i = 0; i < m_bulletsToRemove.size(); i++) {
		std::cout << "Bullet " << m_bulletsToRemove[i] << " being disabled and destroyed" << std::endl;
		BulletObject * bulletToRemove = m_bulletPool->GetObjectById(m_bulletsToRemove[i]);
		bulletToRemove->Disable();
		m_bulletPool->Destroy(m_bulletsToRemove[i]);
	}
	m_bulletsToRemove.clear();
	m_bulletPool->Update(a_dDeltaTime);
}

void BulletManager::OnNotify(Subject *subject)
{
	unsigned int bulletToRemove = dynamic_cast<BulletObject*>(subject)->GetID();
	std::cout << "Bullet " << bulletToRemove << " added to remove list" << std::endl;
	dynamic_cast<BulletObject*>(subject)->RemoveObserver(this);
	m_bulletsToRemove.push_back(bulletToRemove);
}