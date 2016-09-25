#pragma once

#include "PlayerObject.h"
#include "BulletManager.h"

const float ENEMY_F_FIRE_COOL_DOWN_MAX = 0.7f;
const int ENEMY_FIRE_POWER = 3;

class EnemyObject : public ShipObject
{
public:
	EnemyObject(glm::vec3 a_position, PlayerObject* a_player, BulletManager *a_pBulletManager);
	void Update(const double a_dDeltaTime);
private:
	PlayerObject* m_player;
};