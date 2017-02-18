#pragma once
#include "ComponentPool.h"
#include "BulletObject.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "Observer.h"
#include <vector>

class BulletManager : public Observer
{
public:
	BulletManager(ObjectPool<PhysicsComponent> *a_pPhysicsComponentPool, ObjectPool<SpriteComponent> *a_pSpriteComponentPool, ObjectPool<ColliderComponent> *a_pColliderComponentPool,
		GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram *a_pShader);
	void Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_position);
	void Update(const double a_dDeltaTime);
private:
	ObjectPool<SpriteComponent> *m_pSpriteComponentPool;
	ObjectPool<PhysicsComponent> *m_pPhysicsComponentPool;
	ObjectPool<ColliderComponent> *m_pColliderComponentPool;
	
	std::vector<BulletObject*> m_bulletsToRemove;
	int m_iLastAssignedBullet;
	unsigned int m_uiNumActiveBullets;
	ObjectPool<BulletObject>* m_bulletPool;
	GLuint m_uiVAO;
	GLuint m_uiVBO;
	GLuint m_uiIBO;
	GLSLProgram *m_pShader;
	void OnNotify(Subject* subject);
};