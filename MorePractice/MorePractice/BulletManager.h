#pragma once
#include "ComponentPoolHelper.h"
#include "BulletObject.h"
#include "Observer.h"
#include <vector>

class BulletManager : public Observer
{
public:
	BulletManager(ComponentPoolHelper *a_pComponentPoolHelper, GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram * const a_pShader);
	void Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_position);
	void Update(const double a_dDeltaTime);
private:
	ComponentPoolHelper *m_pComponentPoolHelper;
	
	std::vector<unsigned int> m_bulletsToRemove;
	int m_iLastAssignedBullet;
	unsigned int m_uiNumActiveBullets;
	ObjectPool<BulletObject>* m_bulletPool;
	GLuint m_uiVAO;
	GLuint m_uiVBO;
	GLuint m_uiIBO;
	const GLSLProgram *m_pShader;
	void OnNotify(Subject* subject);
};