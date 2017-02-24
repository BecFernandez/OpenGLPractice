#include "BulletObject.h"
#include "ShipObject.h"

BulletObject::BulletObject() : GameObject()
{

}

BulletObject::BulletObject(ObjectPool<PhysicsComponent> *a_pPhysicsPool, ObjectPool<SpriteComponent> *a_pSpritePool, ObjectPool<ColliderComponent> *a_pColliderPool, ShipObject *a_pOwner, int a_iPower, int a_iSpeed, float a_fRotationAngle, glm::vec3 a_startPos, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram* a_pShader)
	: m_pPhysicsPool(a_pPhysicsPool), m_pSpritePool(a_pSpritePool), m_pColliderPool(a_pColliderPool)
{
	m_physicsComponentID = m_pPhysicsPool->Create(1, 1);
	m_spriteComponentID = m_pSpritePool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", a_uiVBO, a_uiIBO, a_pShader);
	m_colliderComponentID = m_pColliderPool->Create(BULLET_COLLIDER, glm::vec2(5.0f, 15.0f));
}

BulletObject::~BulletObject()
{
	
}

void BulletObject::Init(unsigned int a_uiID, ObjectPool<PhysicsComponent> *a_pPhysicsPool, ObjectPool<SpriteComponent> *a_pSpritePool, 
	ObjectPool<ColliderComponent> *a_pColliderPool, ShipObject *a_pOwner, int a_iPower, int a_iSpeed, float a_fRotationAngle, 
	glm::vec3 a_startPos, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram* a_pShader)
{
	m_pPhysicsPool = a_pPhysicsPool;
	m_pSpritePool = a_pSpritePool;
	m_pColliderPool = a_pColliderPool;
	m_uiID = a_uiID;
	std::cout << "bullet created with id: " << m_uiID << std::endl;
	m_physicsComponentID = m_pPhysicsPool->Create(1, 1);
	m_spriteComponentID = m_pSpritePool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 15.0f), "laser.png", a_uiVBO, a_uiIBO, a_pShader);
	m_colliderComponentID = m_pColliderPool->Create(BULLET_COLLIDER, glm::vec2(5.0f, 15.0f));
	AddComponent(PHYSICS, m_pPhysicsPool, m_physicsComponentID);
	AddComponent(SPRITE, m_pSpritePool, m_spriteComponentID);
	AddComponent(COLLIDER, m_pColliderPool, m_colliderComponentID);
	SetActive(true);
}

void BulletObject::Disable()
{
	std::cout << "bullet removed with id: " << m_uiID << std::endl;
	m_pPhysicsPool->Destroy(m_physicsComponentID);
	m_pSpritePool->Destroy(m_spriteComponentID);
	m_pColliderPool->Destroy(m_colliderComponentID);
}

void BulletObject::Update(const double a_dDeltaTime)
{
	if (m_bActive) {
		glm::vec3 position = m_position;

		GameObject::Update(a_dDeltaTime);

		//TODO - move these hard coded references to somewhere central that can be accessed in all files
		if (position.x < 0 || position.x > 800 || position.y < 0 || position.y > 600) {
			m_pOwner = nullptr;
			SetActive(false);
			notify();
		}

		/*if (m_colliderComponent->m_pOtherCollider != nullptr && dynamic_cast<ShipObject*>(m_colliderComponent->m_pOtherCollider->m_pGameObject) != m_pOwner) {
			m_pOwner = nullptr;
			SetActive(false);
			notify();
		}*/
	}
}

void BulletObject::Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_startPos)
{
	m_iPower = a_iPower;
	m_pOwner = a_pOwner;
	//if (m_physicsComponent != nullptr) {
	//	//since the bullet has no friction I should only need to add force once
	//	m_fRotationAngle = a_fRotationAngle;
	//	m_position = a_startPos;
	//	m_physicsComponent->AddForce(glm::vec2(speed, speed));
	//	SetActive(true);
	//}
}