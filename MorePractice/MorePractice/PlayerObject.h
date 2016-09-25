#pragma once
#include "ShipObject.h"
#include "ShaderLoader.h"
#include "BulletManager.h"

const float PLAYER_F_FIRE_COOL_DOWN_MAX = 0.3f;
const int PLAYER_FIRE_POWER = 10;

class PlayerObject : public ShipObject
{
public:
	PlayerObject(glm::vec3 a_position, BulletManager *a_pBulletManager);
	void Update(const double a_dDeltaTime);

private:
	void setComponentPointers();
	PhysicsComponent* m_physicsComponent;
};