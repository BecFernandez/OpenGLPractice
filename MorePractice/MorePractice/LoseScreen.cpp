#include "LoseScreen.h"
#include "MainMenuScreen.h"


LoseScreen::LoseScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : Screen(a_pSounds, a_pShaders),
m_loseImage(glm::vec3(400, 300, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 720, 393, "explosion.jpg"),
//what on earth is going on with this text? I set this every time?? It's the same for each class! Clearly this needs to change
m_loseText(glm::vec3(350, 100, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 256, 256, "arial_0.png", "arial.fnt")
{

}

Screen* LoseScreen::Update(const double a_dDeltaTime)
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

void LoseScreen::Draw()
{
	Screen::Draw();

	//would be a better idea for there to be a list of images and texts, right?
	m_loseImage.Draw(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders);
	m_loseText.DrawString(m_uiSpriteVBO, m_uiSpriteIBO, m_pShaders, "You Lost!");
}