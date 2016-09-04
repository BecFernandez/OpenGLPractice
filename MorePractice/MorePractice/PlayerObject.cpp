#include "PlayerObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"
#include <gtc\matrix_transform.hpp>

PlayerObject::PlayerObject(glm::vec3 a_position, BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader) : 
	ShipObject(a_position, PLAYER_F_FIRE_COOL_DOWN_MAX, a_pBulletManager, a_uiVBO, a_uiIBO, a_pShader)
{

}

void PlayerObject::Update(const double a_dDeltaTime)
{
	if (m_bActive) {
		//don't like calling this - should probably cache a reference or an index.
		//but will worry about fixing it when refactoring component system 
		//to have the components pooled in the scene.
		GLFWwindow* currentContext = glfwGetCurrentContext();
		PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(PHYSICS));
		if (physicsComponent != nullptr) {
			if (glfwGetKey(currentContext, 'W')) {
				physicsComponent->AddForce(glm::vec2(150, 150));
			}

			if (glfwGetKey(currentContext, 'A')) {
				physicsComponent->AddRotation(3);
			}

			if (glfwGetKey(currentContext, 'D')) {
				physicsComponent->AddRotation(-3);
			}
			if (glfwGetKey(currentContext, GLFW_KEY_SPACE)) {
				shoot();
			}
		}
	}

	ShipObject::Update(a_dDeltaTime);
}