#pragma once

#include <glm.hpp>
#include "Component.h"

enum CollisionTags{ 
	PLAYER_COLLIDER,
	ENEMY_COLLIDER,
	BULLET_COLLIDER
};

class ColliderComponent : public Component
{

public:
	ColliderComponent();
	ColliderComponent(CollisionTags a_collisionTag, glm::vec2 a_Dimensions);
	void Init(unsigned int a_uiId, CollisionTags a_collisionTag, glm::vec2 a_Dimensions);
	bool IsCollidingWith(ColliderComponent *a_pOtherCollider);
	void Update(const double a_dDeltaTime);
	ColliderComponent *m_pOtherCollider;
	CollisionTags GetCollisionTag() { return m_collisionTag; }
	void ResetOtherCollider();

private:
	CollisionTags m_collisionTag;
	glm::vec2 min;
	glm::vec2 max;

	glm::vec4 m_corners[4];
};