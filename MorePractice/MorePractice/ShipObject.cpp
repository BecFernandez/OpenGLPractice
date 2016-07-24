#include "ShipObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"
#include <gtc\matrix_transform.hpp>

ShipObject::ShipObject(float a_fFireCoolDownMax, BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader) : 
	m_pBulletManager(a_pBulletManager), m_fFireCoolDownMax(a_fFireCoolDownMax), m_fFireCoolDown(0)
{

}

void ShipObject::Update(const double a_dDeltaTime)
{
	GameObject::Update(a_dDeltaTime);

	m_fFireCoolDown -= a_dDeltaTime;

	SpriteComponent* spriteComponent = dynamic_cast<SpriteComponent*>(GameObject::GetComponent(SPRITE));
	PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(PHYSICS));
	if (spriteComponent != nullptr) {
		if (physicsComponent != nullptr) {
			//Is there a better way to get these components to work together? I feel it's likely to happen a lot.
			spriteComponent->m_position = physicsComponent->m_position;
			spriteComponent->m_fRotationAngle = physicsComponent->m_fRotationAngle;
		}
	}

	HealthComponent* healthComponent = dynamic_cast<HealthComponent*>(GameObject::GetComponent(HEALTH));
	if (!healthComponent->IsAlive()) {
		m_bActive = false;
	}
}


void ShipObject::shoot()
{
	if (m_fFireCoolDown <= 0) {
		m_fFireCoolDown = m_fFireCoolDownMax;
		PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(PHYSICS));
		float rotationAngle = physicsComponent->m_fRotationAngle;
		glm::vec3 shootPos = physicsComponent->m_position;

		//calculate offset from player position in world space
		glm::vec4 offset = glm::rotate(glm::mat4(1), rotationAngle, glm::vec3(0, 0, 1))
			* glm::vec4(10, 0, 0, 1);

		m_pBulletManager->Shoot(M_BULLET_SPEED, rotationAngle, shootPos - glm::vec3(offset.x, offset.y, offset.z));
		m_pBulletManager->Shoot(M_BULLET_SPEED, rotationAngle, shootPos + glm::vec3(2 * offset.x, 2 * offset.y, 2 * offset.z));
	}
}