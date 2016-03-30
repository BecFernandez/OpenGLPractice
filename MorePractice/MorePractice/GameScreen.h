#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__

#include "Screen.h"
#include "Player.h"
#include "Enemy.h"

#include "BulletManager.h"
#include "GameObject.h"

class GameScreen : public Screen
{
public:
	GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders);
	~GameScreen();
	Screen* Update(const double a_dDeltaTime);
	void Draw();

private:
	const unsigned int m_iCOLLISION_DAMAGE = 10;

	std::vector<Bullet*> m_playerBullets;
	std::vector<Bullet*> m_enemyBullets;
	//Player m_player;
	Enemy** m_enemies;

	BulletManager *m_pBulletManager;
	std::vector<GameObject*> m_gameObjects;
};

#endif