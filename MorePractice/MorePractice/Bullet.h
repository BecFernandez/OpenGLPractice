#ifndef __BULLET_H__
#define __BULLET_H__

#include "Sprite.h"

class Bullet: public Sprite
{
private:
	bool m_bOffScreen;

public:
	Bullet(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
		const char *a_szTexName);
	void Update(double a_dDeltaTime);
	void Fire(glm::vec3 a_position, float a_fRotation);
	bool isOffScreen() { return m_bOffScreen;}
};

#endif