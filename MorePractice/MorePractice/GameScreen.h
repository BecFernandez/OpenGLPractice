#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__

#include "Screen.h"
#include "PlayerObject.h"
#include "Enemy.h"

#include "BulletManager.h"
#include "PhysicsManager.h"
#include "ComponentPoolHelper.h"
#include "ComponentPool.h"

class GameScreen : public Screen
{
public:
	GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders);
	~GameScreen();
	Screen* Update(const double a_dDeltaTime);
	void Draw();

private:
	const unsigned int m_iCOLLISION_DAMAGE = 10;

	//std::vector<Bullet*> m_playerBullets;
	//std::vector<Bullet*> m_enemyBullets;
	PlayerObject* m_player;
	//Enemy** m_enemies;

	BulletManager *m_pBulletManager;
	PhysicsManager *m_pPhysicsManager;
	std::vector<GameObject*> m_gameObjects;

	ComponentPoolHelper m_componentPoolHelper;
};

#endif