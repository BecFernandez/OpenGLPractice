#include "GameScreen.h"
#include "LoseScreen.h"
#include "WinScreen.h"

#include "PlayerObject.h"
#include "EnemyObject.h"


GameScreen::GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders) 
{
	float i = 1;
	m_pPhysicsComponentPool = new ObjectPool<PhysicsComponent>(14);
	m_pSpriteComponentPool = new ObjectPool<SpriteComponent>(14);
	m_pColliderComponentPool = new ObjectPool<ColliderComponent>(14);
	m_pHealthComponentPool = new ObjectPool<HealthComponent>(4);
	//m_pSpriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "ship.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	//m_pPhysicsComponentPool->Create(1, 1);

	//ComponentPool<PhysicsComponent> pool(100);

	//m_pPhysicsComponents = new PhysicsComponent[14]{ 
	//	{ 1.0f },  
	//	{ 1.0f },
	//	{ 1.0f },
	//	{ 1.0f },
	//	//yeeeeep, this is shit
	//	{ 1, 1 },
	//	{ 1, 1 },
	//	{ 1, 1 },
	//	{ 1, 1 },
	//	{ 1, 1 },
	//	{ 1, 1 },
	//	{ 1, 1 },
	//	{ 1, 1 },
	//	{ 1, 1 },
	//	{ 1, 1 }
	//};
	/*m_pSpriteComponents = new SpriteComponent[14]{ 
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
	};*/
	/*m_pHealthComponents = new HealthComponent[4]{
		{100},
		{30},
		{30},
		{30}
	};*/

	//m_pColliderComponents = new ColliderComponent[14]{
	//	{ PLAYER_COLLIDER, glm::vec2(51.0f, 86.0f) },
	//	{ ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f) },
	//	{ ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f) },
	//	{ ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) },
	//	{ BULLET_COLLIDER, glm::vec2(5.0f, 15.0f) }
	//};

	m_pBulletManager = new BulletManager(m_pPhysicsComponentPool, m_pSpriteComponentPool, m_pColliderComponentPool, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	m_pPhysicsManager = new PhysicsManager(m_pColliderComponentPool);

	m_player = new PlayerObject(glm::vec3(400, 300, 0), m_pBulletManager);
	m_player->AddComponent(PHYSICS, m_pPhysicsComponentPool, m_pPhysicsComponentPool->Create(1.0f));
	m_player->AddComponent(SPRITE, m_pSpriteComponentPool, m_pSpriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "ship.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
	m_player->AddComponent(HEALTH, m_pHealthComponentPool, m_pHealthComponentPool->Create(100));
	m_player->AddComponent(COLLIDER, m_pColliderComponentPool, m_pColliderComponentPool->Create(PLAYER_COLLIDER, glm::vec2(51.0f, 86.0f)));
	m_gameObjects.push_back(m_player);

	for (int i = 0; i < 3; i++)
	{
		m_gameObjects.push_back(new EnemyObject(glm::vec3(100 + (3-i)%3*250, 100 + i/2*400, 0), m_player, m_pBulletManager));
		m_gameObjects[i + 1]->AddComponent(PHYSICS, m_pColliderComponentPool, m_pPhysicsComponentPool->Create(1.0f));
		m_gameObjects[i + 1]->AddComponent(SPRITE, m_pSpriteComponentPool, m_pSpriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "cylon.png", m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
		m_gameObjects[i + 1]->AddComponent(HEALTH, m_pHealthComponentPool, m_pHealthComponentPool->Create(30));
		m_gameObjects[i + 1]->AddComponent(COLLIDER, m_pColliderComponentPool, m_pColliderComponentPool->Create(ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f)));
	}

	
}

GameScreen::~GameScreen()
{
	//delete[] m_pColliderComponents;
	//delete[] m_pHealthComponents;
	//delete[] m_pPhysicsComponents;
	//delete[] m_pSpriteComponents;

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

	//for (unsigned int i = 0; i < 14; ++i) {
	//	//m_pPhysicsComponents[i].Update(a_fDeltaTime);
	//	m_pSpriteComponents[i].Update(a_fDeltaTime);
	//	m_pColliderComponents[i].Update(a_fDeltaTime);
	//}

	m_pColliderComponentPool->Update(a_fDeltaTime);
	m_pSpriteComponentPool->Update(a_fDeltaTime);
	m_pPhysicsComponentPool->Update(a_fDeltaTime);

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
	for (unsigned int i = 0; i < m_pSpriteComponentPool->GetCurrentSize(); ++i) {
		SpriteComponent* pSpriteComponent = m_pSpriteComponentPool->GetObjectByIndex(i);
		if (pSpriteComponent != nullptr) {
			pSpriteComponent->Draw();
		}
	}
}

