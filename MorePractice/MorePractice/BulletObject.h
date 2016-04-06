#pragma once
#include "GameObject.h"
#include "ShaderLoader.h"
#include "PhysicsComponent.h"

class BulletObject : public GameObject
{
public:
	BulletObject(GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader);
	void Update(const double a_dDeltaTime);
	void Shoot(int speed, float a_fRotationAngle, glm::vec3 a_startPos);
private:
	PhysicsComponent* m_physicsComponent;
};