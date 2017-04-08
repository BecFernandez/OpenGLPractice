#include "ShipObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"
#include "ColliderComponent.h"
#include <gtc\matrix_transform.hpp>

ShipObject::ShipObject(ComponentPoolHelper *a_pComponentPoolHelper, int a_iPower, glm::vec3 a_position, float a_fFireCoolDownMax, BulletManager *a_pBulletManager) : 
	GameObject(a_pComponentPoolHelper, a_position), m_pBulletManager(a_pBulletManager), m_fFireCoolDownMax(a_fFireCoolDownMax), m_fFireCoolDown(0), m_iPower(a_iPower)
{
	GameObject::Update(0);
	SetActive(true);
}

void ShipObject::Update(const double a_dDeltaTime)
{
	GameObject::Update(a_dDeltaTime);

	m_healthComponent = (HealthComponent*)GetComponent(ComponentTypes::HEALTH);
	m_colliderComponent = (ColliderComponent*)GetComponent(ComponentTypes::COLLIDER);
	m_spriteComponent = (SpriteComponent*)GetComponent(ComponentTypes::SPRITE);

	if (m_bActive && !m_healthComponent->IsAlive()) {
		std::cout << "Ship has died :(" << std::endl;
		SetActive(false);
		RemoveComponent(ComponentTypes::HEALTH);
		RemoveComponent(ComponentTypes::COLLIDER);
		RemoveComponent(ComponentTypes::SPRITE);
		RemoveComponent(ComponentTypes::PHYSICS);
	}

	if (m_bActive) {
		if (m_colliderComponent->m_lOtherColliderID != -1) {
			ColliderComponent* otherCollider = m_pComponentPoolHelper->m_colliderComponentPool->GetObjectById(m_colliderComponent->m_lOtherColliderID);
			CollisionTags collisionTag = otherCollider->GetCollisionTag();
			if (collisionTag == PLAYER_COLLIDER || collisionTag == ENEMY_COLLIDER) {
				std::cout << "collision with another ship" << std::endl;
				m_healthComponent->TakeDamage(10);
			}
			else if (collisionTag == BULLET_COLLIDER) {
				BulletObject* bullet = dynamic_cast<BulletObject*>(otherCollider->m_pGameObject);
				if (bullet->m_pOwner != nullptr && bullet->m_pOwner != this) {
					std::cout << "Collision with bullet. Damage: " << bullet->GetPower() << std::endl;
					m_healthComponent->TakeDamage(bullet->GetPower());
				}
			}
		}

		//should really only do this if the health has changed
		float health = m_healthComponent->HealthRatio();
		m_spriteComponent->ChangeColour(glm::vec4(1.0f, health, health, 1.0f));

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

		m_pBulletManager->Shoot(this, m_iPower, M_BULLET_SPEED, m_fRotationAngle, m_position - glm::vec3(offset.x, offset.y, offset.z));
		m_pBulletManager->Shoot(this, m_iPower, M_BULLET_SPEED, m_fRotationAngle, m_position + glm::vec3(2 * offset.x, 2 * offset.y, 2 * offset.z));
	}
}