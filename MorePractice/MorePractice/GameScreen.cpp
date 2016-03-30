#include "GameScreen.h"
#include "LoseScreen.h"
#include "WinScreen.h"

#include "PlayerObject.h"
#include "EnemyObject.h"

GameScreen::GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders) 
//m_player(10, 100, glm::vec3(800 / 2, 600 / 2, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "ship.png", &m_playerBullets, *m_pSounds)
{
	m_enemies = new Enemy*[3];
	for (int i = 0; i < 3; i++)
	{
		m_enemies[i] = new Enemy(1, 50, glm::vec3(rand() % 800, rand() % 600, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "cylon.png", &m_enemyBullets, *m_pSounds);
	}

	m_pBulletManager = new BulletManager(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	m_gameObjects.push_back(new PlayerObject(m_pBulletManager, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
}

GameScreen::~GameScreen()
{
	if (m_enemies != nullptr) {
		for (int i = 0; i < 3; i++) {
			delete m_enemies[i];
		}
		delete m_enemies;
	}

	for (int i = 0; i < m_playerBullets.size(); i++) {
		delete m_playerBullets[i];
	}
	m_playerBullets.clear();

	for (int i = 0; i < m_enemyBullets.size(); i++) {
		delete m_enemyBullets[i];
	}
	m_enemyBullets.clear();

	for (int i = 0; i < m_gameObjects.size(); i++) {
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();
}

Screen* GameScreen::Update(const double a_fDeltaTime)
{
	Screen::Draw();

	m_pBulletManager->Update(a_fDeltaTime);

	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
	{
		return nullptr;
	}

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->Update(a_fDeltaTime);
	}

	bool playerAlive = true;// m_player.IsAlive();

	//update player and enemies
	if (playerAlive) {
		//m_player.Update(a_fDeltaTime, *m_pSounds);

		int aliveCount = 0;
		for (int i = 0; i < 3; i++)
		{
			if (m_enemies[i]->IsAlive()) {
				aliveCount++;
				//m_enemies[i]->Update(m_player.getCentrePos(), a_fDeltaTime, *m_pSounds);
			}
		}
		if (aliveCount == 0) {
			return new WinScreen(m_pSounds, m_pShaders);
		}

		//loop through all bullets
		/*each sprite is calculating its own aabb twice, not so bad with such a small
		number of objects.
		Improvements would be to get the object to store it's own aabb and just update it every frame
		*/

		for (unsigned int i = 0; i < m_enemyBullets.size(); ++i)
		{
			//collisions - player & bullets
			/*if (AABBvsAABB(m_enemyBullets[i]->getAABB(), m_player.getAABB()))
			{
				m_player.Hurt(m_enemyBullets[i]->GetPower());
			}*/
		}

		//collisions player and cylons
		for (unsigned int i = 0; i < 3; ++i)
		{
			/*if (m_enemies[i]->IsAlive() && AABBvsAABB(m_enemies[i]->getAABB(), m_player.getAABB()))
			{
				m_animations.push_back(AnimatedSprite(m_enemies[i]->getCentrePos(), glm::vec4(1, 1, 1, 1),
					55, 55, "ani2.png", 4, 4, 64, 64, 1.0, false));
				m_player.Hurt(m_iCOLLISION_DAMAGE);

			}*/
		}
	}

	for(unsigned int i = 0; i < m_playerBullets.size(); ++i)
	{
		//collisions bullets and cylons
		for(unsigned int j = 0; j < 3; ++j)
		{
			if(m_enemies[j]->IsAlive() && m_playerBullets[i]->GetActive() && AABBvsAABB(m_playerBullets[i]->getAABB(), m_enemies[j]->getAABB()))
			{
				m_enemies[j]->Hurt(m_playerBullets[i]->GetPower());
				//remove cylon
				//add explosion
				m_animations.push_back(AnimatedSprite(m_enemies[j]->getCentrePos(), glm::vec4(1, 1, 1, 1),
					55, 55, "ani2.png", 4, 4, 64, 64, 1.0, false));

				//remove bullet
				m_playerBullets[i]->SetInactive();
			}
		}
	}

	//player died in the last frame
	/*if (playerAlive != m_player.IsAlive()) {
		return new LoseScreen(m_pSounds, m_pShaders);
	}*/

	for (unsigned int i = 0; i < 3; i++)
	{
		if (m_enemies[i]->IsAlive())
			m_enemies[i]->Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	}
	for (unsigned int i = 0; i < m_animations.size(); i++)
	{
		m_animations[i].Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	}

	Screen::Update(a_fDeltaTime);

	return this;
}

void GameScreen::Draw()
{
	//Screen::Draw();

	//draw player
	/*if (m_player.IsAlive()) {
		m_player.Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	}*/
	//draw enemies
	
}

