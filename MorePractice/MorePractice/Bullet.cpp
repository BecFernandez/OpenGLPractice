#include "Bullet.h"
#include <gtc\matrix_transform.hpp>

Bullet::Bullet() : Sprite(), m_bOffScreen(false)
{

}

Bullet::Bullet(const glm::vec3 a_position, const glm::vec4 a_colour, const unsigned int a_uiWidth, const unsigned int a_uiHeight,
	const char *a_szTexName) : Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName), m_bOffScreen(true), m_bActive(true)
{

}

void Bullet::Update(const double a_dDeltaTime)
{
	glm::vec4 temp = glm::rotate(glm::mat4(1), m_fRotationAngle + 90, glm::vec3(0, 0, 1)) 
			* glm::vec4(3, 0, 0, 1);
		//add correctly facing forward vector to existing position
		m_oCentrePos.x += 2*temp.x;
		m_oCentrePos.y += 2*temp.y;

		if(m_oCentrePos.x < 0 || m_oCentrePos.x > 800 || m_oCentrePos.y < 0 || m_oCentrePos.y > 600)
			m_bOffScreen = true;

		Sprite::Update(a_dDeltaTime);
}

void Bullet::Fire(const glm::vec3 a_position, const float a_fRotation)
{
	m_fRotationAngle = a_fRotation;
	m_oCentrePos = a_position;
	m_bOffScreen = false;
}
