#include "EnemyObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"

EnemyObject::EnemyObject(BulletManager *a_pBulletManager, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader) : m_pBulletManager(a_pBulletManager)
{

}

void EnemyObject::Update(double a_dDeltaTime)
{
	m_fFireCoolDown -= a_dDeltaTime;

	PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(PHYSICS));
	SpriteComponent* spriteComponent = dynamic_cast<SpriteComponent*>(GameObject::GetComponent(SPRITE));
	if (spriteComponent != nullptr) {
		if (physicsComponent != nullptr) {
			//Is there a better way to get these components to work together? I feel it's likely to happen a lot.
			spriteComponent->m_position = physicsComponent->m_position;
			spriteComponent->m_fRotationAngle = physicsComponent->m_fRotationAngle;
		}
	}
}