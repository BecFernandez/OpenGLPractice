#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__

#include "Screen.h"
#include "PlayerObject.h"

#include "BulletManager.h"
#include "PhysicsManager.h"

class GameScreen : public Screen
{
public:
	GameScreen(const SoundSystemClass* const a_pSounds, const GLSLProgram * const a_pShaders);
	~GameScreen();
	Screen* Update(const double a_dDeltaTime);
	void Draw();
	void OnNotify(Subject* subject);

private:
	const unsigned int m_iCOLLISION_DAMAGE = 10;
	const unsigned int m_iNUMBER_OF_ENEMIES = 3;
	PlayerObject* m_player;

	BulletManager *m_pBulletManager;
	PhysicsManager *m_pPhysicsManager;
	unsigned int m_uiEnemyCount = m_iNUMBER_OF_ENEMIES;
};

#endif