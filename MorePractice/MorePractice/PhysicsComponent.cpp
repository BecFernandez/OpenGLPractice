#include "PhysicsComponent.h"
#include "GameObject.h"
#include <gtc\matrix_transform.hpp>

PhysicsComponent::PhysicsComponent() : Component(PHYSICS), m_velocity(0, 0), m_acceleration(0, 0), m_fFrictionValue(0.97),
m_fRotationSpeed(1.0f)
{

}

PhysicsComponent::PhysicsComponent(const float a_fRotationSpeed, const float a_fFrictionValue) :
	Component(PHYSICS), m_fRotationSpeed(a_fRotationSpeed),
	m_velocity(0, 0), m_acceleration(0, 0), m_fFrictionValue(a_fFrictionValue)
{

}

void PhysicsComponent::Init(const float a_fRotationSpeed, const float a_fFrictionValue)
{
	m_fRotationSpeed = a_fRotationSpeed;
	m_fFrictionValue = a_fFrictionValue;
}

void PhysicsComponent::AddRotation(const float a_fRotation)
{
	if (m_bActive) {
		m_pGameObject->m_fRotationAngle += a_fRotation;
	}
}

void PhysicsComponent::Update(const double a_dDelaTime)
{
	if (m_bActive) {
		m_velocity.x += m_acceleration.x * a_dDelaTime;
		m_velocity.y += m_acceleration.y * a_dDelaTime;

		glm::vec4 rotationVector = glm::rotate(glm::mat4(1), m_pGameObject->m_fRotationAngle + 90, glm::vec3(0, 0, 1)) * glm::vec4(m_fRotationSpeed, 0, 0, 1);

		m_pGameObject->m_position.x += m_velocity.x * a_dDelaTime * rotationVector.x;
		m_pGameObject->m_position.y += m_velocity.y * a_dDelaTime * rotationVector.y;

		m_velocity *= m_fFrictionValue;

		m_acceleration.x = 0;
		m_acceleration.y = 0;
	}
}