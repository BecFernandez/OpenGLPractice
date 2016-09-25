#include "BulletObject.h"
#include "ShipObject.h"

BulletObject::BulletObject() : m_iPower(0), m_pOwner(nullptr)
{
	SetActive(false);
}

void BulletObject::Update(const double a_dDeltaTime)
{
	glm::vec3 position = m_position;

	GameObject::Update(a_dDeltaTime);

	//TODO - move these hard coded references to somewhere central that can be accessed in all files
	if (position.x < 0 || position.x > 800 || position.y < 0 || position.y > 600) {
		m_pOwner = nullptr;
		SetActive(false);
	}
 
	if (m_colliderComponent->m_pOtherCollider != nullptr && dynamic_cast<ShipObject*>(m_colliderComponent->m_pOtherCollider->m_pGameObject) != m_pOwner) {
		m_pOwner = nullptr;
		SetActive(false);
	}
}

void BulletObject::Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_startPos)
{
	m_iPower = a_iPower;
	m_pOwner = a_pOwner;
	if (m_physicsComponent != nullptr) {
		//since the bullet has no friction I should only need to add force once
		m_fRotationAngle = a_fRotationAngle;
		m_position = a_startPos;
		m_physicsComponent->AddForce(glm::vec2(speed, speed));
		SetActive(true);
	}
}

void BulletObject::setComponentPointers()
{
	m_physicsComponent = dynamic_cast<PhysicsComponent*>(GameObject::GetComponent(PHYSICS));
	m_spriteComponent = dynamic_cast<SpriteComponent*>(GameObject::GetComponent(SPRITE));
	m_colliderComponent = dynamic_cast<ColliderComponent*>(GameObject::GetComponent(COLLIDER));
}