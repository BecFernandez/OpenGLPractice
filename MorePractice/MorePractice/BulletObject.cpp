#include "BulletObject.h"
#include "ShipObject.h"
#include "ResourceManager.h"

BulletObject::BulletObject() : GameObject()
{

}

BulletObject::BulletObject(ComponentPoolHelper *a_pComponentPoolHelper, 
	ShipObject *a_pOwner, int a_iPower, int a_iSpeed, float a_fRotationAngle, glm::vec3 a_startPos, 
	GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader)
	: GameObject(a_pComponentPoolHelper, a_startPos)
{
	m_spriteComponentID = a_pComponentPoolHelper->m_spriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
		&ResourceManager::getInstance().m_textures.GetResource(Levels::GAME_SCREEN, TextureResources::LASER),
		a_uiVAO, a_uiVBO, a_uiIBO, a_pShader);
	m_physicsComponentID = a_pComponentPoolHelper->m_physicsComponentPool->Create(1, 1);
	m_colliderComponentID = a_pComponentPoolHelper->m_colliderComponentPool->Create(BULLET_COLLIDER, glm::vec2(5.0f, 15.0f));
	if (m_spriteComponentID == 0 || m_physicsComponentID == 0 || m_colliderComponentID == 0) {
		std::cout << "A component pool is full" << std::endl;
		//I really need to add some exception handling or something
	}
}

BulletObject::~BulletObject()
{

}

void BulletObject::Init(unsigned int a_uiID, ComponentPoolHelper *a_pComponentPoolHelper,
	ShipObject *a_pOwner, int a_iPower, int a_iSpeed, float a_fRotationAngle, 
	glm::vec3 a_startPos, GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader)
{
	m_pComponentPoolHelper = a_pComponentPoolHelper;
	m_uiID = a_uiID;
	m_spriteComponentID = a_pComponentPoolHelper->m_spriteComponentPool->Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
		&ResourceManager::getInstance().m_textures.GetResource(Levels::GAME_SCREEN, TextureResources::LASER),
		a_uiVAO, a_uiVBO, a_uiIBO, a_pShader);
	m_physicsComponentID = a_pComponentPoolHelper->m_physicsComponentPool->Create(1, 1);
	m_colliderComponentID = a_pComponentPoolHelper->m_colliderComponentPool->Create(BULLET_COLLIDER, glm::vec2(5.0f, 15.0f));
	if (m_spriteComponentID == 0 || m_physicsComponentID == 0 || m_colliderComponentID == 0) {
		std::cout << "A component pool is full" << std::endl;
		//I really need to add some exception handling or something
	}
	ClearObserverList();
	ClearComponentsList();
	AddComponent(ComponentTypes::PHYSICS, m_physicsComponentID);
	AddComponent(ComponentTypes::SPRITE, m_spriteComponentID);
	AddComponent(ComponentTypes::COLLIDER, m_colliderComponentID);
	SetActive(true);
}

void BulletObject::Disable()
{
	m_pComponentPoolHelper->m_spriteComponentPool->Destroy(m_spriteComponentID);
	m_pComponentPoolHelper->m_physicsComponentPool->Destroy(m_physicsComponentID);
	m_pComponentPoolHelper->m_colliderComponentPool->Destroy(m_colliderComponentID);
}

void BulletObject::Update(const double a_dDeltaTime)
{
	if (m_bActive) {
		glm::vec3 position = m_position;

		GameObject::Update(a_dDeltaTime);

		//TODO - move these hard coded numbers to somewhere central that can be accessed in all files
		if (position.x < 0 || position.x > 800 || position.y < 0 || position.y > 600) {
			SetActive(false);
			notify();
			return;
		}

		ColliderComponent* colliderComponent = (ColliderComponent*)GetComponent(ComponentTypes::COLLIDER);
		if (colliderComponent != nullptr) {
			for (unsigned int i = 0; i < colliderComponent->m_OtherColliderIDs.size(); i++) {
				ColliderComponent* otherCollider = (ColliderComponent*)m_pComponentPoolHelper->m_colliderComponentPool->GetObjectById(colliderComponent->m_OtherColliderIDs[i]);
				if (otherCollider != nullptr && dynamic_cast<ShipObject*>(otherCollider->m_pGameObject) != m_pOwner) {
					SetActive(false);
					notify();
					return;
				}
			}
		}
	}
}

void BulletObject::Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_startPos)
{
	m_iPower = a_iPower;
	m_pOwner = a_pOwner;
	PhysicsComponent* pPhysicsComponent = (PhysicsComponent*)GetComponent(ComponentTypes::PHYSICS);
	if (pPhysicsComponent != nullptr) {
		//since the bullet has no friction I should only need to add force once
		m_fRotationAngle = a_fRotationAngle;
		m_position = a_startPos;
		pPhysicsComponent->AddForce(glm::vec2(speed, speed));
		SetActive(true);
	}
}

void BulletObject::PostMoveUpdate()
{
	GameObject::ResetComponentPointers();
}