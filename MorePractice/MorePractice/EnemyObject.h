#pragma once

#include "GameObject.h"
#include "BulletManager.h"

class EnemyObject : public GameObject
{
public:
	EnemyObject(BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader);
	void Update(const double a_dDeltaTime);

private:
	BulletManager *m_pBulletManager;
	float m_fFireCoolDown;
};