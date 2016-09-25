#pragma once
#include "GameObject.h"
#include "ShaderLoader.h"
#include "BulletManager.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"

class ShipObject : public GameObject
{
public:
	ShipObject(int a_iPower, glm::vec3 a_position, float a_fFireCoolDownMax, BulletManager *a_pBulletManager);
	virtual void Update(const double a_dDeltaTime);

protected:
	void shoot();
	virtual void setComponentPointers();

private:
	BulletManager *m_pBulletManager;
	float m_fFireCoolDown;
	float m_fFireCoolDownMax;
	static const int M_BULLET_SPEED = 7000;
	int m_iPower;
	SpriteComponent* m_spriteComponent;
	ColliderComponent* m_colliderComponent;
	HealthComponent* m_healthComponent;
}; 
