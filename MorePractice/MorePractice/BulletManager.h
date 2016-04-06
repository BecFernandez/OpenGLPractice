#pragma once
#include "BulletObject.h"
#include "SpriteComponent.h"

class BulletManager
{
public:
	BulletManager(GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShaderProgram, PhysicsComponent *a_pPhysicsComponents, SpriteComponent *a_pSpriteComponents);
	void Shoot(int speed, float a_fRotationAngle, glm::vec3 a_position);
	void Update(const double a_dDeltaTime);
private:
	GLuint m_uiVBO;
	GLuint m_uiIBO;
	GLSLProgram* m_pShaderProgram;

	SpriteComponent *m_pSpriteComponents;
	PhysicsComponent *m_pPhysicsComponents;

	int m_iLastAssignedBullet;
	unsigned int m_uiNumActiveBullets;
	BulletObject* m_bullets;
};