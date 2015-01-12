#include "Enemy.h"
#include <gtc\matrix_transform.hpp>
#include <cmath>

Enemy::Enemy(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
	const char *a_szTexName) : Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName), m_fSpeed(0)
{

}

void Enemy::Update(glm::vec3 a_oPlayerPos)
{
	//seek towards player?
	glm::vec3 toPlayer = a_oPlayerPos - m_oCentrePos;

	float aimAngle = atan2(toPlayer.y, toPlayer.x);


	if(aimAngle*180.0/3.14159 > m_fRotationAngle + 90)
		m_fRotationAngle += 3;
	else if(aimAngle*180.0/3.14159 < m_fRotationAngle + 90)
		m_fRotationAngle -= 3;

	if(m_fRotationAngle + 90 > 180)
		m_fRotationAngle -= 360;
	else if(m_fRotationAngle + 90 < -180)
		m_fRotationAngle += 360;

	glm::vec4 temp = glm::rotate(glm::mat4(1), m_fRotationAngle + 90, glm::vec3(0, 0, 1)) 
			* glm::vec4(2.5, 0, 0, 1);
		//add correctly facing forward vector to existing position
		m_oCentrePos.x += temp.x;
		m_oCentrePos.y += temp.y;


	Sprite::Update();
}