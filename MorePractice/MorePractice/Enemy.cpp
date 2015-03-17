#include "Enemy.h"
#include <gtc\matrix_transform.hpp>
#include <cmath>

Enemy::Enemy(const glm::vec3 a_position, const glm::vec4 a_colour, const unsigned int a_uiWidth, const unsigned int a_uiHeight,
	const char *a_szTexName, std::vector<Bullet> *a_pBullets, SoundSystemClass a_sounds) : Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName), 
	m_fSpeed(0), m_fFireCoolDown((rand()%10)*0.1), m_pBullets(a_pBullets), m_bAlive(true)
{
	a_sounds.createSound(&m_pLaser, "cylonLaser.wav");
}

void Enemy::Update(const glm::vec3 a_oPlayerPos, const double a_dDeltaTime, SoundSystemClass a_sounds)
{
	if(m_fFireCoolDown > 0)
		m_fFireCoolDown -= a_dDeltaTime;
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
			* glm::vec4(0.5, 0, 0, 1);
		//add correctly facing forward vector to existing position
		m_oCentrePos.x += temp.x;
		m_oCentrePos.y += temp.y;

	//if distance to player is less than 200px then shoot
		if(glm::distance(a_oPlayerPos, m_oCentrePos) < 200  && m_fFireCoolDown <= 0)
		{
			glm::vec4 offset = glm::rotate(glm::mat4(1), m_fRotationAngle, glm::vec3(0, 0, 1)) 
			* glm::vec4(10, 0, 0, 1);
			glm::vec3 shootPos = m_oCentrePos;
			
			shootPos.x -= offset.x;
			shootPos.y -= offset.y;
			//create new bullet
			Bullet newBullet(shootPos, glm::vec4(1.0, 1.0, 1.0, 1.0), 5, 15, "laser.png");
			newBullet.Fire(shootPos, m_fRotationAngle);
			//add to vector
			m_pBullets->push_back(newBullet);

			shootPos.x += 2*offset.x;
			shootPos.y += 2*offset.y;
			//create new bullet
			Bullet newBullet2(shootPos, glm::vec4(1.0, 1.0, 1.0, 1.0), 5, 15, "laser.png");
			newBullet2.Fire(shootPos, m_fRotationAngle);
			//add to vector
			m_pBullets->push_back(newBullet2);
			
			//fire bullet
			m_fFireCoolDown = 0.7;
			a_sounds.playSound(m_pLaser, false);
		}


	Sprite::Update(a_dDeltaTime);

	//update bullets
	for(int i = 0; i < m_pBullets->size(); i++)
	{
		m_pBullets->operator[](i).Update(a_dDeltaTime);
		//remove any bullets that have gone off screen
		if(m_pBullets->operator[](i).isOffScreen())
		{
			m_pBullets->erase(m_pBullets->begin() + i);
			i--;
		}
	}
}

void Enemy::Draw(const GLuint VBO, const GLuint IBO, GLSLProgram *shader) const
{
	Sprite::Draw(VBO, IBO, shader);
	for(int i = 0; i < m_pBullets->size(); i++)
	{
		m_pBullets->operator[](i).Draw(VBO, IBO, shader);
	}
}