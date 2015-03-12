#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Sprite.h"
#include <vector>
#include "Bullet.h"
#include "SoundSystemClass.h"

class Player : public Sprite
{
private:
	//player should only move forward and rotate
	float m_fSpeed;
	std::vector<Bullet> *m_pBullets;
	float m_fFireCoolDown;
	FMOD::Sound *m_pLaser;

public:
	Player(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
		const char *a_szTexName, std::vector<Bullet> *a_pBullets, SoundSystemClass a_sounds);
	void Update(double a_dDeltaTime, SoundSystemClass a_sounds);
	void Draw(GLuint VBO, GLuint IBO, GLSLProgram *shader);
};

#endif