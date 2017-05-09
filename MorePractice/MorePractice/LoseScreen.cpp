#include "LoseScreen.h"
#include "MainMenuScreen.h"


LoseScreen::LoseScreen(const SoundSystemClass* const a_pSounds, const GLSLProgram * const a_pShaders) : Screen(a_pSounds, a_pShaders)
////what on earth is going on with this text? I set this every time?? It's the same for each class! Clearly this needs to change
//m_loseText(glm::vec3(350, 100, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 256, 256, "arial_0.png", "arial.fnt")
{
	m_componentPoolHelper.m_spriteComponentPool = new ObjectPool<SpriteComponent>(1);
	m_gameObjects.push_back(new GameObject(&m_componentPoolHelper, glm::vec3(400, 300, 0)));
	m_gameObjects[0]->AddComponent(ComponentTypes::SPRITE, m_componentPoolHelper.m_spriteComponentPool->Create(glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(720, 393), 
		"explosion.jpg", m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, a_pShaders));

	m_componentPoolHelper.m_fontComponentPool = new ObjectPool<FontComponent>(1);
	m_pMainFont = new GameObject(&m_componentPoolHelper);
	m_pMainFont->AddComponent(ComponentTypes::TEXT, m_componentPoolHelper.m_fontComponentPool->Create(glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec2(256, 256), "arial_0.png", "arial.fnt", m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders));
	m_gameObjects.push_back(m_pMainFont);
}

Screen* LoseScreen::Update(const double a_dDeltaTime)
{
	GLFWwindow *currentContext = glfwGetCurrentContext();
	if (glfwGetKey(currentContext, GLFW_KEY_ESCAPE) ||
		glfwGetKey(currentContext, GLFW_KEY_ENTER) ||
		glfwGetMouseButton(currentContext, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		//why am I passing these two things each time - they are the same for all screens
		//make more sense for them to be static in Screen??
		MainMenuScreen *mms = new MainMenuScreen(m_pSounds, m_pShaders);
		return mms;
	}

	return this;
}

void LoseScreen::Draw()
{
	Screen::Draw();
	FontComponent* font = (FontComponent*)m_pMainFont->GetComponent(ComponentTypes::TEXT);
	font->Draw("You  Lost!", glm::vec3(350, 100, 0));
}