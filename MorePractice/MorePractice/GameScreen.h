#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__

#include "Screen.h"
#include "Player.h"
#include "Enemy.h"

class GameScreen : public Screen
{
private:
	std::vector<Bullet*> m_playerBullets;
	std::vector<Bullet*> m_enemyBullets;
	Player m_player;
	Enemy** m_enemies;
public:
	GameScreen();
	GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders);
	Screen* Update(const double a_dDeltaTime);
	void Draw();
};

#endif