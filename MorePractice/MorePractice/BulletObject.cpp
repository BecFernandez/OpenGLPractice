#include "BulletObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

BulletObject::BulletObject(GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader) : m_physicsComponent(nullptr)
{
	m_bActive = false;
}

void BulletObject::Update(const double a_dDeltaTime)
{
	//don't really like having this check here every frame. Probably would be better to add a virtual function to GameObject that is called at the end of AddComponent that can set this pointer
	if (m_physicsComponent == nullptr) {
		m_physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(PHYSICS));
	}

	glm::vec3 position = m_position;

	GameObject::Update(a_dDeltaTime);

	SpriteComponent* spriteComponent = dynamic_cast<SpriteComponent*>(GameObject::GetComponent(SPRITE));

	//TODO - move these hard coded references to somewhere central that can be accessed in all files
	if (position.x < 0 || position.x > 800 || position.y < 0 || position.y > 600) {
		m_bActive = false;
		spriteComponent->m_bActive = false;
	}

	ColliderComponent* colliderComponent = dynamic_cast<ColliderComponent*>(GameObject::GetComponent(COLLIDER));
	if (colliderComponent->m_pOtherCollider != nullptr) {
		m_bActive = false;
	}
}

void BulletObject::Shoot(int speed, float a_fRotationAngle, glm::vec3 a_startPos)
{
	if (m_physicsComponent != nullptr) {
		//since the bullet has no friction I should only need to add force once
		m_fRotationAngle = a_fRotationAngle;
		m_position = a_startPos;
		m_physicsComponent->AddForce(glm::vec2(speed, speed));
		m_bActive = true;
	}
}