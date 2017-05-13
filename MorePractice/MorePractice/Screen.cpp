#include "Screen.h"
#include <gtc\matrix_transform.hpp>
#include "Vertex.h"
#include "GameObject.h"

void checkGLError(const char* customMessage)
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cout << customMessage << " " << error << std::endl;
	}
}

Screen::Screen() : m_pSounds(nullptr), m_pShaders(nullptr)
{

}

Screen::Screen(const SoundSystemClass* const a_pSounds, const GLSLProgram * const a_pShaders) : m_pSounds(a_pSounds), m_pShaders(a_pShaders)
{
	glGenVertexArrays(1, &m_uiSpriteVAO);
	glBindVertexArray(m_uiSpriteVAO);

	glGenBuffers(1, &m_uiSpriteVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiSpriteVBO);
	//stream draw is to tell OpenGL that the data in this buffer will be modified every frame
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*4, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int spriteIndices[6] = {0, 1, 2, 0, 2, 3};
	glGenBuffers(1, &m_uiSpriteIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiSpriteIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*6, &spriteIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
}

Screen::~Screen()
{

}

Screen* Screen::Update(const double a_dDeltaTime)
{
	m_componentPoolHelper.Update(a_dDeltaTime);

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->Update(a_dDeltaTime);
	}

	//update animations
	/*for(unsigned int i =0; i < m_animations.size(); i++)
	{
		m_animations[i].Update(m_fDeltaTime);
		if(!m_animations[i].IsStillRunning())
		{
			m_animations.erase(m_animations.begin() + i);
			i--;
		}
	}*/
	return this;
}

void Screen::Draw()
{
	m_pShaders->use();
	//set projection view matrix - once per frame
	m_pShaders->setUniform("projectionView", m_projectionMatrix);
	for (unsigned short i = 0; i < m_componentPoolHelper.m_spriteComponentPool->GetCurrentSize(); ++i) {
		SpriteComponent* pSpriteComponent = m_componentPoolHelper.m_spriteComponentPool->GetObjectByIndex(i);
		if (pSpriteComponent != nullptr) {
			pSpriteComponent->Draw();
		}
	}
}

void Screen::OnNotify(Subject * subject)
{
	//nothing here for the moment. This should be overriden in child classes if needed
	//might be best to throw an exception here?
}