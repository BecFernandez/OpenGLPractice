#pragma once
#include "GameObject.h"
#include "ComponentPool.h"
#include "ShaderLoader.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

class ShipObject;

class BulletObject : public GameObject
{
public:
	BulletObject();
	BulletObject(ObjectPool<PhysicsComponent> *a_pPhysicsPool, ObjectPool<SpriteComponent> *a_pSpritePool, ObjectPool<ColliderComponent> *a_pColliderPool, ShipObject *a_pOwner, 
					int a_iPower, int a_iSpeed, float a_fRotationAngle, glm::vec3 a_startPos, GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram* a_pShader);
	~BulletObject();
	void Init(unsigned int a_uiID, ObjectPool<PhysicsComponent> *a_pPhysicsPool, ObjectPool<SpriteComponent> *a_pSpritePool, ObjectPool<ColliderComponent> *a_pColliderPool, ShipObject *a_pOwner,
		int a_iPower, int a_iSpeed, float a_fRotationAngle, glm::vec3 a_startPos, GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram* a_pShader);
	void Update(const double a_dDeltaTime);
	void Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_startPos);
	int GetPower() { return m_iPower; }
	unsigned int GetID() { return m_uiID; }
	ShipObject* m_pOwner;
private:
	PhysicsComponent* m_physicsComponent;
	SpriteComponent* m_spriteComponent;
	ColliderComponent* m_colliderComponent;
	ObjectPool<PhysicsComponent> *m_pPhysicsPool;
	ObjectPool<SpriteComponent> *m_pSpritePool;
	ObjectPool<ColliderComponent> *m_pColliderPool;
	int m_iPower;
	void setComponentPointers();
	unsigned int m_uiID;
};