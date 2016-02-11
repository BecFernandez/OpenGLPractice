#include "WinScreen.h"
#include "MainMenuScreen.h"

WinScreen::WinScreen(SoundSystemClass *a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders),
m_winImage(glm::vec3(0, 0, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 600, 400, "fireworks.jpg"),
m_winText(glm::vec3(350, 100, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 256, 256, "arial_0.png", "arial.fnt")
{

}

Screen *WinScreen::Update(double a_dDeltaTime)
{
	GLFWwindow *currentContext = glfwGetCurrentContext();
	if (glfwGetKey(currentContext, GLFW_KEY_ESCAPE) ||
		glfwGetKey(currentContext, GLFW_KEY_SPACE) ||
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

void WinScreen::Draw()
{
	//why am I doing these two lines each time?? They should be in the base function
	//since they are the same for all classes
	m_pShaders->use();
	m_pShaders->setUniform("projectionView", m_projectionMatrix);

	//would be a better idea for there to be a list of images and texts, right?
	m_winImage.Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	m_winText.DrawString(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, "You Won!");
}