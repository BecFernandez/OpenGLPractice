#include "MainMenuScreen.h"
#include "GameScreen.h"

MainMenuScreen::MainMenuScreen(const SoundSystemClass* const a_pSounds, const GLSLProgram * const a_pShaders) : Screen(a_pSounds, a_pShaders)
	//m_t(glm::vec3(350, 100, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 256, 256, "arial_0.png", "arial.fnt")
{
	m_componentPoolHelper.m_spriteComponentPool = new ObjectPool<SpriteComponent>(1);
	GameObject *mainImageObject = new GameObject(&m_componentPoolHelper, glm::vec3(400, 300, 0));
	mainImageObject->AddComponent(ComponentTypes::SPRITE, m_componentPoolHelper.m_spriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
		glm::vec2(720, 393), "SpaceWars.jpg", m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
	m_gameObjects.push_back(mainImageObject);

	m_componentPoolHelper.m_fontComponentPool = new ObjectPool<FontComponent>(1);
	m_pMainFont = new GameObject(&m_componentPoolHelper);
	m_pMainFont->AddComponent(ComponentTypes::TEXT, m_componentPoolHelper.m_fontComponentPool->Create(glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec2(256, 256), "arial_0.png", "arial.fnt", m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
	m_gameObjects.push_back(m_pMainFont);
}

Screen* MainMenuScreen::Update(const double a_dDeltaTime)
{
	m_componentPoolHelper.Update(a_dDeltaTime);

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

	FontComponent *font = (FontComponent*)m_pMainFont->GetComponent(ComponentTypes::TEXT);
	font->Draw("Hello World!", glm::vec3(350, 100, 0));
}