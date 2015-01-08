#include "Player.h"
#include <gtc\matrix_transform.hpp>

Player::Player(glm::vec3 a_position, glm::vec4 a_colour, unsigned int a_uiWidth, unsigned int a_uiHeight,
	const char *a_szTexName) : Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName), m_fSpeed(0)
{

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

	Sprite::Update();
}