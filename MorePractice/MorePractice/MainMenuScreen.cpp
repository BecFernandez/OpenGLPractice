#include "MainMenuScreen.h"
#include "GameScreen.h"

MainMenuScreen::MainMenuScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders)
	//m_gameTitle(glm::vec3(400, 300, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 720, 393, "SpaceWars.jpg"),
	//m_t(glm::vec3(350, 100, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 256, 256, "arial_0.png", "arial.fnt")
{
	m_pSpriteComponentPool = new ObjectPool<SpriteComponent>(1);
	GameObject *mainImageObject = new GameObject(glm::vec3(400, 300, 0));
	mainImageObject->AddComponent(m_pSpriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(720, 393), "SpaceWars.jpg", m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
	m_gameObjects.push_back(mainImageObject);
}

Screen* MainMenuScreen::Update(const double a_dDeltaTime)
{
	//m_gameTitle.Update(a_dDeltaTime);
	m_pSpriteComponentPool->Update(a_dDeltaTime);

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->Update(a_dDeltaTime);
	}

	//if mouse clicked, change to game screen
	if(glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		GameScreen *gs = new GameScreen(m_pSounds, m_pShaders);
		return gs;
	}

	//if escape pressed, exit game
	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
	{
		return nullptr;
	}

	return this;
}

void MainMenuScreen::Draw()
{
	Screen::Draw();
	for (unsigned int i = 0; i < m_pSpriteComponentPool->GetCurrentSize(); ++i) {
		SpriteComponent* pSpriteComponent = m_pSpriteComponentPool->GetObjectByIndex(i);
		if (pSpriteComponent != nullptr) {
			pSpriteComponent->Draw();
		}
	}

	//m_gameTitle.Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	//checkGLError("draw menu title sprite");
	//m_t.DrawString(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, "Hello  World");
	//checkGLError("draw menu string");
}