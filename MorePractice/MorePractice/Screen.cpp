#include "Screen.h"
#include "Sprite.h"
#include <gtc\matrix_transform.hpp>

Screen::Screen()
{

}

Screen::Screen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders) : m_pSounds(a_pSounds), m_pShaders(a_pShaders)
{
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

Screen* Screen::Update(const double m_fDeltaTime)
{
	//update animations
	for(int i =0; i < m_animations.size(); i++)
	{
		m_animations[i].Update(m_fDeltaTime);
		if(!m_animations[i].IsStillRunning())
		{
			m_animations.erase(m_animations.begin() + i);
			i--;
		}
	}
	return this;
}