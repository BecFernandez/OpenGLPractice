#include "MainMenuScreen.h"
#include "GameScreen.h"

MainMenuScreen::MainMenuScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders),
	m_gameTitle(glm::vec3(400, 300, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 720, 393, "SpaceWars.jpg"),
	m_t(glm::vec3(350, 100, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 256, 256, "arial_0.png", "arial.fnt")
{

}

Screen* MainMenuScreen::Update(const double a_dDeltaTime)
{
	m_gameTitle.Update(a_dDeltaTime);

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
	m_pShaders->use();
	//set projection view matrix - once per frame
	m_pShaders->setUniform("projectionView", m_projectionMatrix);
	m_gameTitle.Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	m_t.DrawString(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, "Hello  World");
}