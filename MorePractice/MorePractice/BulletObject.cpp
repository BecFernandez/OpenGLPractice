#include "BulletObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

BulletObject::BulletObject(int speed, float a_fRotationAngle, glm::vec3 a_startPos, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader)
{
	AddComponent(new SpriteComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f),
		"laser.png", a_uiVBO, a_uiIBO, a_pShader));
	m_physicsComponent = new PhysicsComponent(a_startPos, 1, a_fRotationAngle, 1);
	AddComponent(m_physicsComponent);

	//since the bullet has no friction I should only need to add force once
	m_physicsComponent->AddForce(glm::vec2(speed, speed));
}

void BulletObject::Update(const double a_dDeltaTime)
{
	glm::vec3 position = m_physicsComponent->GetPosition();

	//TODO - move these hard coded references to somewhere central that can be accessed in all files
	if (position.x < 0 || position.x > 800 || position.y < 0 || position.y > 600) {
		m_bActive = false;
	}

	GameObject::Update(a_dDeltaTime);

	SpriteComponent* spriteComponent = dynamic_cast<SpriteComponent*>(GameObject::GetComponent(SPRITE));
	if (spriteComponent != nullptr) {
		if (m_physicsComponent != nullptr) {
			//Is there a better way to get these components to work together? I feel it's likely to happen a lot.
			spriteComponent->m_position = m_physicsComponent->GetPosition();
			spriteComponent->m_fRotationAngle = m_physicsComponent->GetRotation();
		}
		spriteComponent->Draw();
	}
}