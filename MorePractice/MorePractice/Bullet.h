#ifndef __BULLET_H__
#define __BULLET_H__

#include "Sprite.h"

class Bullet: public Sprite
{
public:
	Bullet();
	Bullet(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
		const char *a_szTexName);
	void Fire(float a_fRotationAngle, glm::vec3 a_position);
	void Update();
	bool isActive();
private:
	bool m_bActive;
};

#endif