#include "EnemyObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"

const float PI = 22.0f / 7.0f;

EnemyObject::EnemyObject(ComponentPoolHelper *a_pComponentPoolHelper, glm::vec3 a_position, PlayerObject* a_player, BulletManager *a_pBulletManager) : 
	ShipObject(a_pComponentPoolHelper, ENEMY_FIRE_POWER, a_position, ENEMY_F_FIRE_COOL_DOWN_MAX, a_pBulletManager), m_player(a_player)
{

}

void EnemyObject::Update(double a_dDeltaTime)
{
	ShipObject::Update(a_dDeltaTime);

	if (m_bActive) {
		PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(ComponentTypes::PHYSICS));
		if (physicsComponent != nullptr) {
			glm::vec2 playerHeading = glm::normalize(glm::vec2(glm::cos((m_fRotationAngle-90)*PI / 180), glm::sin((m_fRotationAngle-90)*PI / 180)));
			glm::vec3 toPlayer3D = m_player->m_position - m_position;
			glm::vec2 toPlayer = glm::normalize(glm::vec2(toPlayer3D.x, toPlayer3D.y));
			

			float aimAngle = atan2(playerHeading.y, playerHeading.x);
			aimAngle -= atan2(toPlayer.y, toPlayer.x);

			if (aimAngle > PI) {
				aimAngle -= 2 * PI;
			}
			else if (aimAngle < -1 * PI) {
				aimAngle += 2 * PI;
			}

			std::cout << aimAngle*180.0 / PI + 90 << std::endl;

			if (aimAngle*180.0 / PI > m_fRotationAngle + 90)
				physicsComponent->AddRotation(3);
			else if (aimAngle*180.0 / PI < m_fRotationAngle + 90)
				physicsComponent->AddRotation(-3);

			if (m_fRotationAngle +90 > 180)
				physicsComponent->AddRotation(-360);
			else if (m_fRotationAngle + 90 < -180)
				physicsComponent->AddRotation(360);

			physicsComponent->AddForce(glm::vec2(50, 50));


			if (glm::distance(m_player->m_position, m_position) < 200) {
				ShipObject::shoot();
			}
		}
	}
}