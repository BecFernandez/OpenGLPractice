#include "EnemyObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"

EnemyObject::EnemyObject(ComponentPoolHelper *a_pComponentPoolHelper, glm::vec3 a_position, PlayerObject* a_player, BulletManager *a_pBulletManager) : 
	ShipObject(a_pComponentPoolHelper, ENEMY_FIRE_POWER, a_position, ENEMY_F_FIRE_COOL_DOWN_MAX, a_pBulletManager), m_player(a_player)
{

}

void EnemyObject::Update(double a_dDeltaTime)
{
	if (m_bActive) {
		PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(ComponentTypes::PHYSICS));
		if (physicsComponent != nullptr) {
			glm::vec3 playerPos = m_player->m_position;

			glm::vec3 toPlayer = playerPos - m_position;

			float aimAngle = atan2(toPlayer.y, toPlayer.x);

			if (aimAngle*180.0 / 3.14159 > m_fRotationAngle + 90)
				physicsComponent->AddRotation(3);
			else if (aimAngle*180.0 / 3.14159 < m_fRotationAngle + 90)
				physicsComponent->AddRotation(-3);

			if (m_fRotationAngle + 90 > 180)
				physicsComponent->AddRotation(-360);
			else if (m_fRotationAngle + 90 < -180)
				physicsComponent->AddRotation(360);

			physicsComponent->AddForce(glm::vec2(50, 50));


			if (glm::distance(playerPos, m_position) < 200) {
				ShipObject::shoot();
			}
		}
	}

	ShipObject::Update(a_dDeltaTime);
}