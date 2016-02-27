#include "PlayerObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

PlayerObject::PlayerObject(GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader)
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
	}

	SpriteComponent* spriteComponent = dynamic_cast<SpriteComponent*>(GameObject::GetComponent(SPRITE));
	if (spriteComponent != nullptr) {
		spriteComponent->Draw();
	}
}