#pragma once
#include "BulletObject.h"

class BulletManager
{
public:
	BulletManager(GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShaderProgram);
	void Shoot(float a_fRotationAngle, glm::vec3 a_position);
	void Update(const double a_dDeltaTime);
private:
	GLuint m_uiVBO;
	GLuint m_uiIBO;
	GLSLProgram* m_pShaderProgram;
	//yes, will pool this too once I get to pooling things
	std::vector<BulletObject*> m_bullets;
};