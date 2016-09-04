#pragma once

#include <glm.hpp>
#include "Component.h"

enum CollisionTags{ 
	PLAYER,
	ENEMY,
	BULLET
};

class ColliderComponent : public Component
{

public:
	ColliderComponent(CollisionTags a_collisionTag, glm::vec2 a_Dimensions);
	bool IsCollidingWith(ColliderComponent *a_pOtherCollider);
	void Update(const double a_dDeltaTime);
	ColliderComponent *m_pOtherCollider;

private:
	CollisionTags m_collisionTag;
	glm::vec2 min;
	glm::vec2 max;

	glm::vec4 m_corners[4];
};