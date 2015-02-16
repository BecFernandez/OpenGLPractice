#include "Player.h"
#include <gtc\matrix_transform.hpp>

Player::Player(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
	const char *a_szTexName) : Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName), m_fSpeed(0), m_fFireCoolDown(0)
{
	
}


void Player::Update(double a_dDeltaTime)
{
	if(m_fFireCoolDown > 0)
		m_fFireCoolDown -= a_dDeltaTime;

	//move forward
	if(glfwGetKey(glfwGetCurrentContext(), 'W'))
	{
		//rotate "forward 3 units" by current rotation
		glm::vec4 temp = glm::rotate(glm::mat4(1), m_fRotationAngle + 90, glm::vec3(0, 0, 1)) 
			* glm::vec4(3, 0, 0, 1);
		//add correctly facing forward vector to existing position
		m_oCentrePos.x += temp.x;
		m_oCentrePos.y += temp.y;
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

	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) && m_fFireCoolDown <= 0)
	{
		//create new bullet 
		glm::vec4 offset = glm::rotate(glm::mat4(1), m_fRotationAngle, glm::vec3(0, 0, 1)) 
			* glm::vec4(10, 0, 0, 1);
		glm::vec3 shootPos = m_oCentrePos;
		shootPos.x -= offset.x;
		shootPos.y -= offset.y;
		Bullet newBullet(shootPos, glm::vec4(1.0, 1.0, 1.0, 1.0), 5, 15, "laser.png");
		newBullet.Fire(shootPos, m_fRotationAngle);
		//add to vector
		bullets.push_back(newBullet);
		shootPos.x += 2*offset.x;
		shootPos.y += 2*offset.y;
		Bullet newBullet2(shootPos, glm::vec4(1.0, 1.0, 1.0, 1.0), 5, 15, "laser.png");
		newBullet2.Fire(shootPos, m_fRotationAngle);
		//add to vector
		bullets.push_back(newBullet2);
		//fire bullet
		m_fFireCoolDown = 0.3;
	}

	Sprite::Update(a_dDeltaTime);

	for(int i = 0; i < bullets.size(); i++)
	{
		bullets[i].Update(a_dDeltaTime);
		if(bullets[i].isOffScreen())
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void Player::Draw(GLuint VBO, GLuint IBO, GLSLProgram *shader)
{
	Sprite::Draw(VBO, IBO, shader);
	for(int i = 0; i < bullets.size(); i++)
	{
		bullets[i].Draw(VBO, IBO, shader);
	}
}