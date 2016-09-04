#include "ColliderComponent.h"
#include "GameObject.h"
#include <gtc\matrix_transform.hpp>

ColliderComponent::ColliderComponent(CollisionTags a_collisionTag, glm::vec2 a_Dimensions) : Component(COLLIDER), m_collisionTag(a_collisionTag), m_pOtherCollider(nullptr)
{
	for (int i = 0; i < 4; i++)
	{
		m_corners[i].z = 0;
		m_corners[i].w = 1;

		if (i / 2)
		{
			m_corners[i].x = a_Dimensions.x *0.5f * (float)-1;
		}
		else
		{
			m_corners[i].x = a_Dimensions.x*0.5f;
		}
		if (i % 3)
		{
			m_corners[i].y = a_Dimensions.y*0.5f;
		}
		else
		{
			m_corners[i].y = a_Dimensions.y*0.5f * (float)-1;
		}
	}
}

void ColliderComponent::Update(const double a_dDeltaTime)
{
	min.x = max.x = m_pGameObject->m_position.x;
	min.y = max.y = m_pGameObject->m_position.y;

	glm::mat4 globalTransform = glm::translate(glm::mat4(1), glm::vec3(m_pGameObject->m_position.x, m_pGameObject->m_position.y, m_pGameObject->m_position.z)) *
		glm::rotate(glm::mat4(1), m_pGameObject->m_fRotationAngle, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(m_pGameObject->m_fScale, m_pGameObject->m_fScale, 1));

	for (unsigned int i = 0; i < 4; ++i)
	{
		glm::vec4 temp = globalTransform * m_corners[i];
		if (temp.x < min.x)
			min.x = temp.x;
		if (temp.y < min.y)
			min.y = temp.y;
		if (temp.x > max.x)
			max.x = temp.x;
		if (temp.y > max.y)
			max.y = temp.y;
	}
}

bool ColliderComponent::IsCollidingWith(ColliderComponent *a_pOtherCollider)
{
	m_pOtherCollider = nullptr;
	if (!m_pGameObject->IsActive()) {
		return false;
	}
	if (m_collisionTag == a_pOtherCollider->m_collisionTag) {
		return false;
	}
	if (max.x < a_pOtherCollider->min.x || min.x > a_pOtherCollider->max.x)
		return false;
	if (max.y < a_pOtherCollider->min.y || min.y > a_pOtherCollider->max.y)
		return false;
	//store the other collider
	m_pOtherCollider = a_pOtherCollider;
	return true;
}