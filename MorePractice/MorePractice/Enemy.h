#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Sprite.h"

class Enemy : public Sprite
{
private:
	//player should only move forward and rotate
	float m_fSpeed;

public:
	Enemy(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
		const char *a_szTexName);
	void Update(glm::vec3 a_oPlayerPos);
};

#endif