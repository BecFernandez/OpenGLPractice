#pragma once
#include "GameObject.h"
#include "ShaderLoader.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

class ShipObject;

class BulletObject : public GameObject
{
public:
	BulletObject();
	void Update(const double a_dDeltaTime);
	void Shoot(ShipObject* a_pOwner, int a_iPower, int speed, float a_fRotationAngle, glm::vec3 a_startPos);
	int GetPower() { return m_iPower; }
	ShipObject* m_pOwner;
private:
	PhysicsComponent* m_physicsComponent;
	SpriteComponent* m_spriteComponent;
	ColliderComponent* m_colliderComponent;
	int m_iPower;
	void setComponentPointers();
};