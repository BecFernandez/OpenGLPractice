#include "BulletManager.h"

BulletManager::BulletManager(GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShaderProgram, PhysicsComponent *a_pPhysicsComponents, SpriteComponent *a_pSpriteComponents, ColliderComponent *a_pColliderComponents) :
	m_uiVBO(a_uiVBO), m_uiIBO(a_uiIBO), m_pShaderProgram(a_pShaderProgram), m_pPhysicsComponents(a_pPhysicsComponents), m_pSpriteComponents(a_pSpriteComponents), m_pColliderComponents(a_pColliderComponents),
	m_iLastAssignedBullet(-1), m_uiNumActiveBullets(0)
{
	m_bullets = new BulletObject[10]{
		//ok, this is shit - gotta find a better way of doing this.
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{ m_uiVBO, m_uiIBO, m_pShaderProgram },
		{m_uiVBO, m_uiIBO, m_pShaderProgram}
	};
	for (unsigned int i = 0; i < 10; ++i) {
		m_bullets[i].AddComponent(m_pPhysicsComponents + i);
		m_bullets[i].AddComponent(m_pSpriteComponents + i);
		m_bullets[i].AddComponent(m_pColliderComponents + i);
	}
}

void BulletManager::Shoot(int speed, float a_fRotationAngle, glm::vec3 a_position) 
{
	//clearly need to make this 10 a const (or a variable if I pass it in, I guess)
	if (m_uiNumActiveBullets < 10) {
		while (true) { //is this bad? My teachers (and I) always taught it was bad coding practice - but otherwise I'm wasting a boolean and an extra check
			++m_iLastAssignedBullet;
			if (m_iLastAssignedBullet >= 10) {
				m_iLastAssignedBullet = 0;
			}
			if (!m_bullets[m_iLastAssignedBullet].IsActive()) {
				m_bullets[m_iLastAssignedBullet].Shoot(speed, a_fRotationAngle, a_position);
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