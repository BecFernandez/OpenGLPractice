#include "MainMenuScreen.h"
#include "GameScreen.h"
#include "ResourceManager.h"

MainMenuScreen::MainMenuScreen(const SoundSystemClass* const a_pSounds) : Screen(a_pSounds, Levels::MAIN_SCREEN)
{
	m_pSpriteShader = ResourceManager::getInstance().m_shaders.GetResource(Levels::GLOBAL, ShaderResources::DEFAULT_SPRITE);
	m_pFontShader = ResourceManager::getInstance().m_shaders.GetResource(Levels::GLOBAL, ShaderResources::ARIAL_FONT);
	m_componentPoolHelper.m_spriteComponentPool = new ObjectPool<SpriteComponent>(1);
	m_gameObjects.push_back(new GameObject(&m_componentPoolHelper, glm::vec3(400, 300, 0)));
	m_gameObjects[0]->AddComponent(ComponentTypes::SPRITE, m_componentPoolHelper.m_spriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
		ResourceManager::getInstance().m_textures.GetResource(Levels::MAIN_SCREEN, TextureResources::SPACE_WARS), 
		m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pSpriteShader));

	m_componentPoolHelper.m_fontComponentPool = new ObjectPool<FontComponent>(1);
	m_pMainFont = new GameObject(&m_componentPoolHelper);
	m_pMainFont->AddComponent(ComponentTypes::TEXT, m_componentPoolHelper.m_fontComponentPool->Create(glm::vec4(1.0, 0.0, 0.0, 1.0),
		ResourceManager::getInstance().m_textures.GetResource(Levels::GLOBAL, TextureResources::ARIAL_0), 
		ResourceManager::getInstance().m_fonts.GetResource(Levels::GLOBAL, FontResources::ARIAL_0),
		m_uiSpriteVAO, m_uiSpriteVBO, m_uiSpriteIBO, m_pFontShader));
	m_gameObjects.push_back(m_pMainFont);
}

Screen* MainMenuScreen::Update(const double a_dDeltaTime)
{
	Screen::Update(a_dDeltaTime);

	//if mouse clicked, change to game screen
	if(glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		GameScreen *gs = new GameScreen(m_pSounds);
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

	
	m_pFontShader->use();
	m_pFontShader->setUniform("projectionView", m_projectionMatrix);
	FontComponent *font = (FontComponent*)m_pMainFont->GetComponent(ComponentTypes::TEXT);
	font->Draw("Hello World!", glm::vec3(350, 100, 0));
}