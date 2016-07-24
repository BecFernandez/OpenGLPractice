#pragma once
#include "GameObject.h"
#include "ShaderLoader.h"
#include "BulletManager.h"

class ShipObject : public GameObject
{
public:
	ShipObject(float a_fFireCoolDownMax, BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader);
	virtual void Update(const double a_dDeltaTime);

protected:
	void shoot();

private:
	BulletManager *m_pBulletManager;
	float m_fFireCoolDown;
	float m_fFireCoolDownMax;
	static const int M_BULLET_SPEED = 30000;
}; 
