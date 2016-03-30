#pragma once
#include "GameObject.h"
#include "ShaderLoader.h"
#include "PhysicsComponent.h"

class BulletObject : public GameObject
{
public:
	BulletObject(int speed, float a_fRotationAngle, glm::vec3 a_startPos, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader);
	void Update(const double a_dDeltaTime);
private:
	PhysicsComponent* m_physicsComponent;
};