#include "GameScreen.h"
#include "LoseScreen.h"
#include "WinScreen.h"

#include "PlayerObject.h"
#include "EnemyObject.h"

GameScreen::GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders) 
//m_player(10, 100, glm::vec3(800 / 2, 600 / 2, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "ship.png", &m_playerBullets, *m_pSounds)
{
	m_pPhysicsComponents = new PhysicsComponent[14]{ 
		{ glm::vec3(400, 300, 0), 1.0f, 0.0f, 0.97f },  
		{},
		{},
		{},
		//yeeeeep, this is shit
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false },
		{ glm::vec3(), 1, 0.0f, 1, false }
	};
	m_pSpriteComponents = new SpriteComponent[14]{ 
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "ship.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "cylon.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "cylon.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "cylon.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, false }
	};
	m_pHealthComponents = new HealthComponent[4]{
		{100},
		{30},
		{30},
		{30}
	};

	m_pBulletManager = new BulletManager(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, m_pPhysicsComponents + 4, m_pSpriteComponents + 4);

	m_player = new PlayerObject(m_pBulletManager, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	m_player->AddComponent(m_pPhysicsComponents);
	m_player->AddComponent(m_pSpriteComponents);
	m_player->AddComponent(m_pHealthComponents);
	m_gameObjects.push_back(m_player);

	//m_enemies = new Enemy*[3];
	for (int i = 0; i < 3; i++)
	{
		m_gameObjects.push_back(new EnemyObject(m_pBulletManager, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
		m_gameObjects[i + 1]->AddComponent(m_pPhysicsComponents + i + 1);
		m_gameObjects[i + 1]->AddComponent(m_pSpriteComponents + i + 1);
		m_gameObjects[i + 1]->AddComponent(m_pHealthComponents + i + 1);
		//m_enemies[i] = new Enemy(1, 50, glm::vec3(rand() % 800, rand() % 600, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "cylon.png", &m_enemyBullets, *m_pSounds);
	}

	
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

	for (unsigned int i = 0; i < 14; ++i) {
		m_pPhysicsComponents[i].Update(a_fDeltaTime);
		m_pSpriteComponents[i].Update(a_fDeltaTime);
	}

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->Update(a_fDeltaTime);
	}

	bool playerAlive =  m_player->IsActive();

	if (playerAlive) {

		int aliveCount = 0;
		//for (int i = 0; i < 3; i++)
		//{
		//	if (m_enemies[i]->IsAlive()) {
		//		aliveCount++;
		//		//m_enemies[i]->Update(m_player.getCentrePos(), a_fDeltaTime, *m_pSounds);
		//	}
		//}
		//if (aliveCount == 0) {
		//	return new WinScreen(m_pSounds, m_pShaders);
		//}

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

	//for(unsigned int i = 0; i < m_playerBullets.size(); ++i)
	//{
	//	//collisions bullets and cylons
	//	for(unsigned int j = 0; j < 3; ++j)
	//	{
	//		if(m_enemies[j]->IsAlive() && m_playerBullets[i]->GetActive() && AABBvsAABB(m_playerBullets[i]->getAABB(), m_enemies[j]->getAABB()))
	//		{
	//			m_enemies[j]->Hurt(m_playerBullets[i]->GetPower());
	//			//remove cylon
	//			//add explosion
	//			m_animations.push_back(AnimatedSprite(m_enemies[j]->getCentrePos(), glm::vec4(1, 1, 1, 1),
	//				55, 55, "ani2.png", 4, 4, 64, 64, 1.0, false));

	//			//remove bullet
	//			m_playerBullets[i]->SetInactive();
	//		}
	//	}
	//}

	//player died in the last frame
	if (playerAlive != m_player->IsActive()) {
		return new LoseScreen(m_pSounds, m_pShaders);
	}

	/*for (unsigned int i = 0; i < 3; i++)
	{
		if (m_enemies[i]->IsAlive())
			m_enemies[i]->Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	}*/
	for (unsigned int i = 0; i < m_animations.size(); i++)
	{
		m_animations[i].Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	}

	Screen::Update(a_fDeltaTime);

	return this;
}

void GameScreen::Draw()
{
	Screen::Draw();

	for (unsigned int i = 0; i < 14; ++i) {
		m_pSpriteComponents[i].Draw();
	}

	//draw player
	/*if (m_player.IsAlive()) {
		m_player.Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	}*/
	//draw enemies
	
}

