#include "Player.h"
#include <gtc\matrix_transform.hpp>

Player::Player(const float a_fPower, const float a_fHealth, const glm::vec3 a_position, const glm::vec4 a_colour, const unsigned int a_uiWidth, const unsigned int a_uiHeight,
	const char *a_szTexName, std::vector<Bullet*> *a_pBullets, SoundSystemClass a_sounds) : Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName), 
	m_fSpeed(0), m_fFireCoolDown(0), m_pBullets(a_pBullets), m_fPower(a_fPower), m_fHealth(a_fHealth), m_fOriginalHealth(a_fHealth), m_bAlive(true)
{
	a_sounds.createSound(&m_pLaser, "laser.wav");
}


void Player::Update(const double a_dDeltaTime, SoundSystemClass a_sounds)
{
	//update velocity
	m_oVelocity.x += m_oAcceleration.x * a_dDeltaTime;
	m_oVelocity.y += m_oAcceleration.y * a_dDeltaTime;

	glm::vec4 temp = glm::rotate(glm::mat4(1), m_fRotationAngle + 90, glm::vec3(0, 0, 1)) 
			* glm::vec4(3, 0, 0, 1);

	//update position
	m_oCentrePos.x += m_oVelocity.x * a_dDeltaTime * temp.x;
	m_oCentrePos.y += m_oVelocity.y * a_dDeltaTime * temp.y;
	
	//apply friction
	m_oVelocity *= 0.97;

	//move forward
	if(glfwGetKey(glfwGetCurrentContext(), 'W'))
	{
		m_oAcceleration.x = 150;
		m_oAcceleration.y = 150;
	}
	else
	{
		m_oAcceleration.x = 0;
		m_oAcceleration.y = 0;
	}

	//rotate right
	if(glfwGetKey(glfwGetCurrentContext(),'A'))
	{
		m_fRotationAngle += 3;
	}
	//rotate left
	if(glfwGetKey(glfwGetCurrentContext(),'D'))
	{
		m_fRotationAngle -= 3;
	}

	//update shooting cooldown timer
	if(m_fFireCoolDown > 0)
		m_fFireCoolDown -= a_dDeltaTime;

	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) && m_fFireCoolDown <= 0)
	{
		//calculate offset from player position in world space
		glm::vec4 offset = glm::rotate(glm::mat4(1), m_fRotationAngle, glm::vec3(0, 0, 1)) 
			* glm::vec4(10, 0, 0, 1);
		glm::vec3 shootPos = m_oCentrePos;
		//apply offset
		shootPos.x -= offset.x;
		shootPos.y -= offset.y;
		//create new bullet
		Bullet *newBullet = new Bullet(m_fPower, shootPos, glm::vec4(1.0, 1.0, 1.0, 1.0), 5, 15, "laser.png");
		newBullet->Fire(shootPos, m_fRotationAngle);
		//add to vector
		m_pBullets->push_back(newBullet);
		//adjust offset and apply to other bullet
		shootPos.x += 2*offset.x;
		shootPos.y += 2*offset.y;
		//create another bullet
		Bullet *newBullet2 = new Bullet(m_fPower, shootPos, glm::vec4(1.0, 1.0, 1.0, 1.0), 5, 15, "laser.png");
		newBullet2->Fire(shootPos, m_fRotationAngle);
		//add to vector
		m_pBullets->push_back(newBullet2);
		//set cooldown timer
		m_fFireCoolDown = 0.3;
		//play bullet sound
		a_sounds.playSound(m_pLaser, false);
	}

	

	Sprite::Update(a_dDeltaTime);

	//update bullets
	for(unsigned int i = 0; i < m_pBullets->size(); i++)
	{
		m_pBullets->operator[](i)->Update(a_dDeltaTime);
		//remove any bullets that have gone off screen or have collided with anything
		if(m_pBullets->operator[](i)->isOffScreen() || m_pBullets->operator[](i)->GetActive() == false)
		{
			delete m_pBullets->operator[](i);
			m_pBullets->erase(m_pBullets->begin() + i);
			i--;
		}
	}
}

void Player::Draw(const GLuint VBO, const GLuint IBO, GLSLProgram *shader) const
{
	Sprite::Draw(VBO, IBO, shader);
	for(unsigned int i = 0; i < m_pBullets->size(); i++)
	{
		m_pBullets->operator[](i)->Draw(VBO, IBO, shader);
	}
}

void Player::Hurt(const float a_fDamage)
{
	m_fHealth -= a_fDamage;
	if (m_fHealth < 0) {
		m_bAlive = false;
	}
	else {
		this->changeColour(glm::vec4(1, m_fHealth / m_fOriginalHealth, m_fHealth / m_fOriginalHealth, 1));
	}
}