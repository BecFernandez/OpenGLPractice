#include "Bullet.h"
#include <gtc\matrix_transform.hpp>

Bullet::Bullet() : Sprite(), m_bActive(false)
{
	
}

Bullet::Bullet(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
	const char *a_szTexName) : Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName), m_bActive(false)
{
	
}

void Bullet::Fire(float a_fRotationAngle, glm::vec3 a_position)
{
	m_oCentrePos = a_position;
	m_fRotationAngle = a_fRotationAngle;
	m_bActive = true;
}

void Bullet::Update()
{
	glm::vec4 temp = glm::rotate(glm::mat4(1), m_fRotationAngle + 90, glm::vec3(0, 0, 1)) 
			* glm::vec4(6, 0, 0, 1);
		//add correctly facing forward vector to existing position
		m_oCentrePos.x += temp.x;
		m_oCentrePos.y += temp.y;

		//if bullet is outside window, set active to false;

	Sprite::Update();
}

bool Bullet::isActive()
{
	return m_bActive;
}