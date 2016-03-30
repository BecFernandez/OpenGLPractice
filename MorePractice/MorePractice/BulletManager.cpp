#include "BulletManager.h"

BulletManager::BulletManager(GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShaderProgram) :
	m_uiVBO(a_uiVBO), m_uiIBO(a_uiIBO), m_pShaderProgram(a_pShaderProgram)
{

}

void BulletManager::Shoot(int speed, float a_fRotationAngle, glm::vec3 a_position) 
{
	m_bullets.push_back(new BulletObject(speed, a_fRotationAngle, a_position, m_uiVBO, m_uiIBO, m_pShaderProgram));
}

void BulletManager::Update(const double a_dDeltaTime)
{
	for (int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i]->Update(a_dDeltaTime);
		if (!m_bullets[i]->IsActive()) {
			delete m_bullets[i];
			m_bullets.erase(m_bullets.begin() + i);
			i--;
		}
	}
}