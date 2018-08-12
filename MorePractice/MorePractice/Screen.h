#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "GL\glew.h"
#include "SoundSystemClass.h"
#include "ShaderLoader.h"
#include <glm.hpp>
#include <vector>
#include "AnimatedSprite.h"
#include "Observer.h"
#include "ComponentPoolHelper.h"
#include "ResourceEnums.h"

class Screen : public Observer
{
public:
	Screen();
	Screen(const SoundSystemClass* const a_pSounds, Levels level); 
	virtual ~Screen();
	virtual Screen* Update(const double a_dDeltaTime);
	virtual void Draw();
	virtual void OnNotify(Subject* subject);

protected:
	const SoundSystemClass* const m_pSounds;
	GLSLProgram * m_pSpriteShader;
//	std::vector<AnimatedSprite> m_animations;
	glm::mat4 m_projectionMatrix;
	ComponentPoolHelper m_componentPoolHelper;
	std::vector<GameObject*> m_gameObjects;
	Levels m_level;
	GLuint m_uiSpriteVAO;
	GLuint m_uiSpriteVBO;
	GLuint m_uiSpriteIBO;
};

void checkGLError(const char* customMessage);

#endif