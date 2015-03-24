#include "GameScreen.h"

GameScreen::GameScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders), 
	m_player(glm::vec3(800/2, 600/2, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "ship.png", &m_playerBullets, *m_pSounds)
{
	m_enemies = new Enemy*[3];
	for(int i = 0; i < 3; i++)
	{
		m_enemies[i] = new Enemy(glm::vec3(rand()%800, rand()%600, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "cylon.png", &m_enemyBullets, *m_pSounds);
	}
}

Screen* GameScreen::Update(const double a_fDeltaTime)
{
	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
	{
		return nullptr;
	}

	//update player and enemies
	m_player.Update(a_fDeltaTime, *m_pSounds);
	for(int i = 0; i < 3; i++)
	{
		if(m_enemies[i]->IsAlive())
			m_enemies[i]->Update(m_player.getCentrePos(), a_fDeltaTime, *m_pSounds);
	}

	//loop through all bullets
	/*each sprite is calculating its own aabb twice, not so bad with such a small 
	number of objects.
	Improvements would be to get the object to store it's own aabb and just update it every frame
	*/
	for(unsigned int i = 0; i < m_enemyBullets.size(); ++i)
	{
		//collisions - player & bullets
		if(AABBvsAABB(m_enemyBullets[i].getAABB(), m_player.getAABB()))
		{
			m_player.changeColour(glm::vec4(1, 0, 0, 1));
		}
	}
	for(unsigned int i = 0; i < m_playerBullets.size(); ++i)
	{
		//collisions bullets and cylons
		for(unsigned int j = 0; j < 3; ++j)
		{
			if(m_enemies[j]->IsAlive() && AABBvsAABB(m_playerBullets[i].getAABB(), m_enemies[j]->getAABB()))
			{
				m_enemies[j]->Kill();
				//remove cylon
				//add explosion
				m_animations.push_back(AnimatedSprite(m_enemies[j]->getCentrePos(), glm::vec4(1, 1, 1, 1),
					55, 55, "ani2.png", 4, 4, 64, 64, 1.0, false));
			}
		}
	}

	//collisions player and cylons
	for(unsigned int i = 0; i < 3; ++i)
	{
		if(m_enemies[i]->IsAlive() && AABBvsAABB(m_enemies[i]->getAABB(), m_player.getAABB()))
		{
			m_enemies[i]->Kill();
			m_animations.push_back(AnimatedSprite(m_enemies[i]->getCentrePos(), glm::vec4(1, 1, 1, 1),
					55, 55, "ani2.png", 4, 4, 64, 64, 1.0, false));
			m_player.changeColour(glm::vec4(1, 0, 0, 1));
		}
	}

	Screen::Update(a_fDeltaTime);

	return this;
}

void GameScreen::Draw()
{
	m_pShaders->use();
	//set projection view matrix - once per frame
	m_pShaders->setUniform("projectionView", m_projectionMatrix);

	//draw player
	m_player.Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	//draw enemies
	for(int i = 0; i < 3; i++)
	{
		if(m_enemies[i]->IsAlive())
			m_enemies[i]->Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	}
	for(int i = 0; i < m_animations.size(); i++)
	{
		m_animations[i].Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	}
}

