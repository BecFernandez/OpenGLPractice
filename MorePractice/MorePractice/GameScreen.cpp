#include "GameScreen.h"
#include "LoseScreen.h"
#include "WinScreen.h"

#include "PlayerObject.h"
#include "EnemyObject.h"

GameScreen::GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders) 
{
	m_pPhysicsComponents = new PhysicsComponent[14]{ 
		{ 1.0f },  
		{ 1.0f },
		{ 1.0f },
		{ 1.0f },
		//yeeeeep, this is shit
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 }
	};
	m_pSpriteComponents = new SpriteComponent[14]{ 
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "ship.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "cylon.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "cylon.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "cylon.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders },
		{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders }
	};
	m_pHealthComponents = new HealthComponent[4]{
		{100},
		{30},
		{30},
		{30}
	};

	m_pColliderComponents = new ColliderComponent[14]{
		{ PLAYER_COLLIDER, glm::vec2(51.0f, 86.0f) },
		{ ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f) },
		{ ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f) },
		{ ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
		{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) }
	};

	m_pBulletManager = new BulletManager(m_pPhysicsComponents + 4, m_pSpriteComponents + 4, m_pColliderComponents + 4);
	m_pPhysicsManager = new PhysicsManager();
	for (unsigned int i = 0; i < 14; i++) {
		m_pPhysicsManager->AddCollider(&m_pColliderComponents[i]);
	}

	m_player = new PlayerObject(glm::vec3(400, 300, 0), m_pBulletManager);
	m_player->AddComponent(m_pPhysicsComponents);
	m_player->AddComponent(m_pSpriteComponents);
	m_player->AddComponent(m_pHealthComponents);
	m_player->AddComponent(m_pColliderComponents);
	m_gameObjects.push_back(m_player);

	for (int i = 0; i < 3; i++)
	{
		m_gameObjects.push_back(new EnemyObject(glm::vec3(100 + (3-i)%3*250, 100 + i/2*400, 0), m_player, m_pBulletManager));
		m_gameObjects[i + 1]->AddComponent(m_pPhysicsComponents + i + 1);
		m_gameObjects[i + 1]->AddComponent(m_pSpriteComponents + i + 1);
		m_gameObjects[i + 1]->AddComponent(m_pHealthComponents + i + 1);
		m_gameObjects[i + 1]->AddComponent(m_pColliderComponents + i + 1);
		//m_enemies[i] = new Enemy(1, 50, glm::vec3(rand() % 800, rand() % 600, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "cylon.png", &m_enemyBullets, *m_pSounds);
	}

	
}

GameScreen::~GameScreen()
{
	delete[] m_pColliderComponents;
	delete[] m_pHealthComponents;
	delete[] m_pPhysicsComponents;
	delete[] m_pSpriteComponents;

	for (int i = 0; i < m_gameObjects.size(); i++) {
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();
}

Screen* GameScreen::Update(const double a_fDeltaTime)
{
	bool playerAlive = m_player->IsActive();

	Screen::Draw();

	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
	{
		return nullptr;
	}

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->Update(a_fDeltaTime);
	}

	for (unsigned int i = 0; i < 14; ++i) {
		m_pPhysicsComponents[i].Update(a_fDeltaTime);
		m_pSpriteComponents[i].Update(a_fDeltaTime);
		m_pColliderComponents[i].Update(a_fDeltaTime);
	}

	m_pBulletManager->Update(a_fDeltaTime);
	m_pPhysicsManager->Update();

	//player died in the last frame
	if (playerAlive != m_player->IsActive()) {
		return new LoseScreen(m_pSounds, m_pShaders);
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
	Screen::Draw();

	for (unsigned int i = 0; i < 14; ++i) {
		m_pSpriteComponents[i].Draw();
	}
}

