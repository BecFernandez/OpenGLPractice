#include "Physics.h"

bool AABBvsAABB(AABB a, AABB b)
{
	if(a.max.x < b.min.x || a.min.x > b.max.x)
		return false;
	if(a.max.y < b.min.y || a.min.y > b.max.y)
		return false;
	return true;
}

float Distance(glm::vec2 a, glm::vec2 b)
{
	return (a-b).length();
}

bool CirclevsCircle(Circle a, Circle b)
{
	float r = a.radius + b.radius;
	return r < Distance(a.position, b.position);
}

bool CirclevsCircleOptimised(Circle a, Circle b)
{
	float r = a.radius + b.radius;
	r *= r;
	return r < (a.position.x + b.position.x)*(a.position.x + b.position.x) + (a.position.y + b.position.y)*(a.position.y + b.position.y);
}