#include "Player.h"
#include <gtc\matrix_transform.hpp>

Player::Player(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
	const char *a_szTexName) : Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName), m_fSpeed(0)
{
	for(unsigned short i = 0; i < 30; ++i)
	{
		m_bullets[i].setTexture("bullet.png");
	}
}


void Player::Update()
{
	//move forward
	if(glfwGetKey('W'))
	{
		//rotate "forward 3 units" by current rotation
		glm::vec4 temp = glm::rotate(glm::mat4(1), m_fRotationAngle + 90, glm::vec3(0, 0, 1)) 
			* glm::vec4(3, 0, 0, 1);
		//add correctly facing forward vector to existing position
		m_oCentrePos.x += temp.x;
		m_oCentrePos.y += temp.y;
	}

	//rotate right
	if(glfwGetKey('A'))
	{
		m_fRotationAngle += 3;
	}
	//rotate left
	if(glfwGetKey('D'))
	{
		m_fRotationAngle -= 3;
	}

	if(glfwGetKey(GLFW_KEY_SPACE))
	{
		for(unsigned short i = 0; i < 30; ++i)
		{
			if(!m_bullets[i].isActive())
			{
				m_bullets[i].Fire(m_fRotationAngle, m_oCentrePos);
				break;
			}
		}
	}

	Sprite::Update();

	for(unsigned short i = 0; i < 30; ++i)
	{
		if(m_bullets[i].isActive())
			m_bullets[i].Update();
	}
}

void Player::Draw(GLuint VBO, GLuint IBO, GLSLProgram *shader)
{
	for(unsigned short i = 0; i < 30; ++i)
	{
		if(m_bullets[i].isActive())
			m_bullets[i].Draw(VBO, IBO, shader);
	}

	Sprite::Draw(VBO, IBO, shader);
}