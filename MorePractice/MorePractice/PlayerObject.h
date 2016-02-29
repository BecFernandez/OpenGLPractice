#pragma once
#include "GameObject.h"
#include "ShaderLoader.h"
#include "BulletManager.h"

class PlayerObject : public GameObject
{
public:
	PlayerObject(BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader);
	void Update(const double a_dDeltaTime);

private:
	BulletManager *m_pBulletManager;
	float m_fFireCoolDown;
	void shoot();
};