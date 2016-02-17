#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "GL\glew.h"
#include "SoundSystemClass.h"
#include "ShaderLoader.h"
#include <glm.hpp>
#include <vector>
#include "AnimatedSprite.h"

class Screen
{
public:
	Screen();
	Screen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders); 
	virtual ~Screen();
	virtual Screen* Update(const double a_dDeltaTime);
	virtual void Draw();

protected:
	SoundSystemClass* m_pSounds;
	GLSLProgram *m_pShaders;
	GLuint m_uiSpriteVBO;
	GLuint m_uiSpriteIBO;
	std::vector<AnimatedSprite> m_animations;
	glm::mat4 m_projectionMatrix;
};

#endif