#include "ColliderComponent.h"
#include "GameObject.h"
#include <gtc\matrix_transform.hpp>

ColliderComponent::ColliderComponent() : Component(ComponentTypes::COLLIDER)
{
	m_pOtherColliderID = -1;
}

ColliderComponent::ColliderComponent(CollisionTags a_collisionTag, glm::vec2 a_Dimensions) : Component(ComponentTypes::COLLIDER), m_collisionTag(a_collisionTag)
{
	m_collisionTag = a_collisionTag;
	m_pOtherColliderID = -1;
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

void ColliderComponent::Init(unsigned int a_uiId, CollisionTags a_collisionTag, glm::vec2 a_Dimensions)
{
	m_collisionTag = a_collisionTag;
	m_pOtherColliderID = -1;
	m_uiID = a_uiId;

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

	for (unsigned int i = 0; i < 4; ++i)
	{
		glm::vec4 temp = m_pGameObject->GetGlobalTransform() * m_corners[i];
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

void ColliderComponent::ResetOtherCollider()
{
	m_pOtherColliderID = -1;
}

bool ColliderComponent::IsCollidingWith(ColliderComponent *a_pOtherCollider)
{
	if (m_collisionTag == a_pOtherCollider->m_collisionTag) {
		return false;
	}
	if (max.x < a_pOtherCollider->min.x || min.x > a_pOtherCollider->max.x)
		return false;
	if (max.y < a_pOtherCollider->min.y || min.y > a_pOtherCollider->max.y)
		return false;
	//store the other collider
	std::cout << "Collision: " << a_pOtherCollider->GetID() << " " << GetID() << std::endl;
	m_pOtherColliderID = a_pOtherCollider->GetID();
	//a_pOtherCollider->m_pOtherCollider = this;
	return true;
}