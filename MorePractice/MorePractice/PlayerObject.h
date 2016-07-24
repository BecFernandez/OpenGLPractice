#pragma once
#include "ShipObject.h"
#include "ShaderLoader.h"
#include "BulletManager.h"

const float PLAYER_F_FIRE_COOL_DOWN_MAX = 0.3f;

class PlayerObject : public ShipObject
{
public:
	PlayerObject(BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader);
	void Update(const double a_dDeltaTime);
	glm::vec3 GetPosition() const;
};