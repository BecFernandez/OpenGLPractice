#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <glm.hpp>

struct AABB
{
	glm::vec2 min;
	glm::vec2 max;
};

struct Circle
{
	float radius;
	glm::vec2 position;
};

bool AABBvsAABB(AABB a, AABB b);
float Distance(glm::vec2 a, glm::vec2 b);
bool CirclevsCircle(Circle a, Circle b);
bool CirclevsCircleOptimised(Circle a, Circle b);

#endif