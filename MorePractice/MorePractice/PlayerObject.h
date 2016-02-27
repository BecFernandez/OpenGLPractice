#pragma once
#include "GameObject.h"
#include "ShaderLoader.h"

class PlayerObject : public GameObject
{
public:
	PlayerObject(GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader);
	void Update(const double a_dDeltaTime);
};