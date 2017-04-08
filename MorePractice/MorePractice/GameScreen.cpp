#include "GameScreen.h"
#include "LoseScreen.h"
#include "WinScreen.h"

#include "PlayerObject.h"
#include "EnemyObject.h"


GameScreen::GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders) 
{
	float i = 1;
	m_componentPoolHelper.m_physicsComponentPool = new ObjectPool<PhysicsComponent>(14);
	m_componentPoolHelper.m_spriteComponentPool = new ObjectPool<SpriteComponent>(14);
	m_componentPoolHelper.m_colliderComponentPool = new ObjectPool<ColliderComponent>(14);
	m_componentPoolHelper.m_healthComponentPool = new ObjectPool<HealthComponent>(4);

	m_pBulletManager = new BulletManager(&m_componentPoolHelper, m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	m_pPhysicsManager = new PhysicsManager(&m_componentPoolHelper);

	m_player = new PlayerObject(&m_componentPoolHelper, glm::vec3(400, 300, 0), m_pBulletManager);
	m_player->AddComponent(ComponentTypes::PHYSICS, m_componentPoolHelper.m_physicsComponentPool->Create(1.0f));
	m_player->AddComponent(ComponentTypes::SPRITE, m_componentPoolHelper.m_spriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "ship.png", m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
	m_player->AddComponent(ComponentTypes::HEALTH, m_componentPoolHelper.m_healthComponentPool->Create(100));
	m_player->AddComponent(ComponentTypes::COLLIDER, m_componentPoolHelper.m_colliderComponentPool->Create(PLAYER_COLLIDER, glm::vec2(51.0f, 86.0f)));
	m_gameObjects.push_back(m_player);

	for (int i = 0; i < 1; i++)
	{
		m_gameObjects.push_back(new EnemyObject(&m_componentPoolHelper, glm::vec3(100 + (3-i)%3*250, 100 + i/2*400, 0), m_player, m_pBulletManager));
		m_gameObjects[i + 1]->AddComponent(ComponentTypes::PHYSICS, m_componentPoolHelper.m_physicsComponentPool->Create(1.0f));
		m_gameObjects[i + 1]->AddComponent(ComponentTypes::SPRITE, m_componentPoolHelper.m_spriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f), "cylon.png", m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
		m_gameObjects[i + 1]->AddComponent(ComponentTypes::HEALTH, m_componentPoolHelper.m_healthComponentPool->Create(30));
		m_gameObjects[i + 1]->AddComponent(ComponentTypes::COLLIDER, m_componentPoolHelper.m_colliderComponentPool->Create(ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f)));
	}

	
}

GameScreen::~GameScreen()
{
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

	m_pBulletManager->Update(a_fDeltaTime);
	
	m_componentPoolHelper.Update(a_fDeltaTime);

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
	//this code is the same in both screens, perhaps it should be moved elsewhere?
	Screen::Draw();
	for (unsigned short i = 0; i < m_componentPoolHelper.m_spriteComponentPool->GetCurrentSize(); ++i) {
		SpriteComponent* pSpriteComponent = m_componentPoolHelper.m_spriteComponentPool->GetObjectByIndex(i);
		if (pSpriteComponent != nullptr) {
			pSpriteComponent->Draw();
		}
	}
}

