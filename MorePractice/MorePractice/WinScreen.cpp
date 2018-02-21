#include "WinScreen.h"
#include "MainMenuScreen.h"
#include "ResourceManager.h"

WinScreen::WinScreen(const SoundSystemClass * const a_pSounds) : Screen(a_pSounds)
{
	m_pSpriteShader = &ResourceManager::getInstance().m_shaders.GetResource(Levels::GLOBAL, ShaderResources::DEFAULT_SPRITE);
	m_componentPoolHelper.m_spriteComponentPool = new ObjectPool<SpriteComponent>(1);
	m_gameObjects.push_back(new GameObject(&m_componentPoolHelper, glm::vec3(400, 300, 0)));
	m_gameObjects[0]->AddComponent(ComponentTypes::SPRITE, m_componentPoolHelper.m_spriteComponentPool->Create(glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(600, 400), "fireworks.jpg",
		m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pSpriteShader));

	m_componentPoolHelper.m_fontComponentPool = new ObjectPool<FontComponent>(1);
	m_pMainFont = new GameObject(&m_componentPoolHelper);
	m_pMainFont->AddComponent(ComponentTypes::TEXT, m_componentPoolHelper.m_fontComponentPool->Create(glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec2(256, 256), "arial_0.png", "arial.fnt", m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pSpriteShader));
	m_gameObjects.push_back(m_pMainFont);
}

Screen *WinScreen::Update(double a_dDeltaTime)
{
	Screen::Update(a_dDeltaTime);

	GLFWwindow *currentContext = glfwGetCurrentContext();
	if (glfwGetKey(currentContext, GLFW_KEY_ESCAPE) ||
		glfwGetKey(currentContext, GLFW_KEY_SPACE) ||
		glfwGetKey(currentContext, GLFW_KEY_ENTER) ||
		glfwGetMouseButton(currentContext, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		//why am I passing these two things each time - they are the same for all screens
		//make more sense for them to be static in Screen??
		MainMenuScreen *mms = new MainMenuScreen(m_pSounds);
		return mms;
	}

	return this;
}

void WinScreen::Draw()
{
	Screen::Draw();

	FontComponent* font = (FontComponent*)m_pMainFont->GetComponent(ComponentTypes::TEXT);
	font->Draw("You  Won!", glm::vec3(350, 100, 0));
}