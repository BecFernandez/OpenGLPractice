#include "ShipObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"
#include "ColliderComponent.h"
#include <gtc\matrix_transform.hpp>

ShipObject::ShipObject(glm::vec3 a_position, float a_fFireCoolDownMax, BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader) : GameObject(a_position),
	m_pBulletManager(a_pBulletManager), m_fFireCoolDownMax(a_fFireCoolDownMax), m_fFireCoolDown(0)
{

}

void ShipObject::Update(const double a_dDeltaTime)
{
	GameObject::Update(a_dDeltaTime);

	HealthComponent* healthComponent = dynamic_cast<HealthComponent*>(GameObject::GetComponent(HEALTH));
	if (!healthComponent->IsAlive()) {
		m_bActive = false;
	}

	if (m_bActive) {
		//check collisions here?
		ColliderComponent* colliderComponent = dynamic_cast<ColliderComponent*>(GameObject::GetComponent(COLLIDER));
		if (colliderComponent->m_pOtherCollider != nullptr) {
			//ok, this means there has been a collision
			//check if collision is ship object or bullet
			if (dynamic_cast<ShipObject*>(colliderComponent->m_pOtherCollider->m_pGameObject)) {
				//inflict damage
				healthComponent->TakeDamage(10);
			}
			else if (dynamic_cast<BulletObject*>(colliderComponent->m_pOtherCollider->m_pGameObject)) {
				//inflict damage
				healthComponent->TakeDamage(10); //really this needs to be the power of the other bullet
			}
		}

		m_fFireCoolDown -= a_dDeltaTime;
	}
}


void ShipObject::shoot()
{
	if (m_fFireCoolDown <= 0) {
		m_fFireCoolDown = m_fFireCoolDownMax;

		//calculate offset from player position in world space
		glm::vec4 offset = glm::rotate(glm::mat4(1), m_fRotationAngle, glm::vec3(0, 0, 1))
			* glm::vec4(10, 0, 0, 1);

		m_pBulletManager->Shoot(M_BULLET_SPEED, m_fRotationAngle, m_position - glm::vec3(offset.x, offset.y, offset.z));
		m_pBulletManager->Shoot(M_BULLET_SPEED, m_fRotationAngle, m_position + glm::vec3(2 * offset.x, 2 * offset.y, 2 * offset.z));
	}
}