#include "GameScreen.h"
#include "LoseScreen.h"
#include "WinScreen.h"
#include "ResourceManager.h"
#include "PlayerObject.h"
#include "EnemyObject.h"


GameScreen::GameScreen(const SoundSystemClass* const a_pSounds) : Screen(a_pSounds, Levels::GAME_SCREEN)
{
	m_pSpriteShader = ResourceManager::getInstance().m_shaders.GetResource(Levels::GLOBAL, ShaderResources::DEFAULT_SPRITE);
	float i = 1;
	m_componentPoolHelper.m_physicsComponentPool = new ObjectPool<PhysicsComponent>(14);
	m_componentPoolHelper.m_spriteComponentPool = new ObjectPool<SpriteComponent>(14);
	m_componentPoolHelper.m_colliderComponentPool = new ObjectPool<ColliderComponent>(14);
	m_componentPoolHelper.m_healthComponentPool = new ObjectPool<HealthComponent>(4);

	m_pBulletManager = new BulletManager(&m_componentPoolHelper, m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pSpriteShader);
	m_pPhysicsManager = new PhysicsManager(&m_componentPoolHelper);

	m_player = new PlayerObject(&m_componentPoolHelper, glm::vec3(400, 300, 0), m_pBulletManager);
	m_player->AddComponent(ComponentTypes::PHYSICS, m_componentPoolHelper.m_physicsComponentPool->Create(1.0f));
	m_player->AddComponent(ComponentTypes::SPRITE, m_componentPoolHelper.m_spriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
		ResourceManager::getInstance().m_textures.GetResource(Levels::GAME_SCREEN, TextureResources::SHIP), 
		m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pSpriteShader));
	m_player->AddComponent(ComponentTypes::HEALTH, m_componentPoolHelper.m_healthComponentPool->Create(100));
	m_player->AddComponent(ComponentTypes::COLLIDER, m_componentPoolHelper.m_colliderComponentPool->Create(PLAYER_COLLIDER, glm::vec2(51.0f, 86.0f)));
	m_gameObjects.push_back(m_player);

	for (unsigned int i = 0; i < m_iNUMBER_OF_ENEMIES; i++)
	{
		m_gameObjects.push_back(new EnemyObject(&m_componentPoolHelper, glm::vec3(100 + (3-i)%3*250, 100 + i/2*400, 0), m_player, m_pBulletManager));
		m_gameObjects[i + 1]->AddComponent(ComponentTypes::PHYSICS, m_componentPoolHelper.m_physicsComponentPool->Create(1.0f));
		m_gameObjects[i + 1]->AddComponent(ComponentTypes::SPRITE, m_componentPoolHelper.m_spriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
			ResourceManager::getInstance().m_textures.GetResource(Levels::GAME_SCREEN, TextureResources::CYLON), 
			m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pSpriteShader));
		m_gameObjects[i + 1]->AddComponent(ComponentTypes::HEALTH, m_componentPoolHelper.m_healthComponentPool->Create(30));
		m_gameObjects[i + 1]->AddComponent(ComponentTypes::COLLIDER, m_componentPoolHelper.m_colliderComponentPool->Create(ENEMY_COLLIDER, glm::vec2(51.0f, 86.0f)));
		m_gameObjects[i + 1]->AddObserver(this);
	}
}

GameScreen::~GameScreen()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();
}

Screen* GameScreen::Update(const double a_dDeltaTime)
{
	Screen::Update(a_dDeltaTime);

	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
	{
		return nullptr;
	}

	m_pBulletManager->Update(a_dDeltaTime);

	m_pPhysicsManager->Update();

	if (!m_player->IsActive()) {
		return new LoseScreen(m_pSounds);
	}

	if (m_uiEnemyCount == 0) {
		return new WinScreen(m_pSounds);
	}

	//for (unsigned int i = 0; i < m_animations.size(); i++)
	//{
	//	m_animations[i].Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	//}

	return this;
}

void GameScreen::Draw()
{
	Screen::Draw();
}

void GameScreen::OnNotify(Subject *subject)
{
	if (dynamic_cast<EnemyObject*>(subject)) {
		this->m_uiEnemyCount--;
	}
}

