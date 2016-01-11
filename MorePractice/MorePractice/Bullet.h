#ifndef __BULLET_H__
#define __BULLET_H__

#include "Sprite.h"

class Bullet: public Sprite
{
private:
	bool m_bOffScreen;
	bool m_bActive;

public:
	Bullet();
	Bullet(const glm::vec3 a_position, const glm::vec4 a_colour, const unsigned int a_uiWidth, const unsigned int a_uiHeight,
		const char *a_szTexName);
	void Update(const double a_dDeltaTime);
	void Fire(const glm::vec3 a_position, const float a_fRotation);
	bool isOffScreen() const { return m_bOffScreen;}
	void SetInactive() { m_bActive = false; }
	bool GetActive() const { return m_bActive; }
};

#endif