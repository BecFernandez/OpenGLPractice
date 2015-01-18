#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Sprite.h"
#include "Bullet.h"

class Player : public Sprite
{
private:
	//player should only move forward and rotate
	float m_fSpeed;
	Bullet m_bullets[30];

public:
	Player(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
		const char *a_szTexName);
	void Update();
	void Draw(GLuint VBO, GLuint IBO, GLSLProgram *shader);
};

#endif