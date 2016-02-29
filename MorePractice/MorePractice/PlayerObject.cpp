#include "PlayerObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include <gtc\matrix_transform.hpp>

PlayerObject::PlayerObject(BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader) : m_pBulletManager(a_pBulletManager)
{
	AddComponent(new SpriteComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(51.0f, 86.0f),
		"ship.png", a_uiVBO, a_uiIBO, a_pShader));
	AddComponent(new PhysicsComponent());
}

void PlayerObject::Update(const double a_dDeltaTime)
{
	GameObject::Update(a_dDeltaTime);

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

	SpriteComponent* spriteComponent = dynamic_cast<SpriteComponent*>(GameObject::GetComponent(SPRITE));
	if (spriteComponent != nullptr) {
		if (physicsComponent != nullptr) {
			//Is there a better way to get these components to work together? I feel it's likely to happen a lot.
			spriteComponent->m_position = physicsComponent->GetPosition();
			spriteComponent->m_fRotationAngle = physicsComponent->GetRotation();
		}
		spriteComponent->Draw();
	}
}

void PlayerObject::shoot()
{
	if (m_fFireCoolDown <= 0) {
		m_fFireCoolDown = 0.3f;
		PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(PHYSICS));
		float rotationAngle = physicsComponent->GetRotation();
		glm::vec3 shootPos = physicsComponent->GetPosition();

		//calculate offset from player position in world space
		glm::vec4 offset = glm::rotate(glm::mat4(1), rotationAngle, glm::vec3(0, 0, 1))
			* glm::vec4(10, 0, 0, 1);

		m_pBulletManager->Shoot(rotationAngle, shootPos - glm::vec3(offset.x, offset.y, offset.z));
		m_pBulletManager->Shoot(rotationAngle, shootPos + glm::vec3(2*offset.x, 2*offset.y, 2*offset.z));
	}
}