#include "PlayerObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"
#include <gtc\matrix_transform.hpp>

PlayerObject::PlayerObject(ComponentPoolHelper *a_pComponentPoolHelper, glm::vec3 a_position, BulletManager *a_pBulletManager) : 
	ShipObject(a_pComponentPoolHelper, PLAYER_FIRE_POWER, a_position, PLAYER_F_FIRE_COOL_DOWN_MAX, a_pBulletManager)
{

}

void PlayerObject::Update(const double a_dDeltaTime)
{
	ShipObject::Update(a_dDeltaTime);
	m_physicsComponent = (PhysicsComponent*)GetComponent(ComponentTypes::PHYSICS);
	
	if (m_bActive) {
		GLFWwindow* currentContext = glfwGetCurrentContext();
		if (m_physicsComponent != nullptr) {
			if (glfwGetKey(currentContext, 'W')) {
				m_physicsComponent->AddForce(glm::vec2(250, 250));
			}

			if (glfwGetKey(currentContext, 'A')) {
				m_physicsComponent->AddRotation(3);
			}

			if (glfwGetKey(currentContext, 'D')) {
				m_physicsComponent->AddRotation(-3);
			}
			if (glfwGetKey(currentContext, GLFW_KEY_SPACE)) {
				shoot();
			}
		}
	}
}