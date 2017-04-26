#pragma once
#include "GameObject.h"
#include "ComponentPool.h"
#include "ShaderLoader.h"
#include "ComponentPoolHelper.h"

class ShipObject;

class BulletObject : public GameObject
{
public:
	BulletObject();
	BulletObject(ComponentPoolHelper *a_pComponentPoolHelper, ShipObject *a_pOwner, int a_iPower, int a_iSpeed, 
		float a_fRotationAngle, glm::vec3 a_startPos, GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader);
	~BulletObject();
	void Init(unsigned int a_uiID, ComponentPoolHelper *a_pComponentPoolHelper, ShipObject *a_pOwner, int a_iPower, 
		int a_iSpeed, float a_fRotationAngle, glm::vec3 a_startPos, GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader);
	void Disable();
	void Update(const double a_dDeltaTime);
	void Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_startPos);
	void PostMoveUpdate();
	int GetPower() { return m_iPower; }
	unsigned int GetID() { return m_uiID; }
	ShipObject* m_pOwner;
private:
	unsigned int m_physicsComponentID;
	unsigned int m_spriteComponentID;
	unsigned int m_colliderComponentID;
	int m_iPower;
	unsigned int m_uiID;
};