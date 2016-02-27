#include "PhysicsComponent.h"
#include <gtc\matrix_transform.hpp>

const float PhysicsComponent::m_fFrictionValue = 0.97;

PhysicsComponent::PhysicsComponent() : Component(PHYSICS), m_position(0, 0, 0), m_fRotationSpeed(1), m_fRotationAngle(0),
m_velocity(0, 0), m_acceleration(0, 0)
{

}

PhysicsComponent::PhysicsComponent(const glm::vec3 a_position, const float a_fRotationSpeed, const float a_fRotationAngle) :
	Component(PHYSICS), m_position(a_position), m_fRotationSpeed(a_fRotationSpeed), m_fRotationAngle(a_fRotationAngle), 
	m_velocity(0, 0), m_acceleration(0, 0)
{

}

void PhysicsComponent::AddForce(const glm::vec2 a_force)
{
	m_acceleration += a_force;
}

void PhysicsComponent::AddRotation(const float a_fRotation)
{
	m_fRotationAngle += a_fRotation;
}

void PhysicsComponent::Update(const double a_dDelaTime)
{
	m_velocity.x += m_acceleration.x * a_dDelaTime;
	m_velocity.y += m_acceleration.y * a_dDelaTime;

	glm::vec4 rotationVector = glm::rotate(glm::mat4(1), m_fRotationAngle + 90, glm::vec3(0, 0, 1)) * glm::vec4(m_fRotationSpeed, 0, 0, 1);

	m_position.x += m_velocity.x * a_dDelaTime * rotationVector.x;
	m_position.y += m_velocity.y * a_dDelaTime * rotationVector.y;

	m_velocity *= m_fFrictionValue;

	m_acceleration.x = 0;
	m_acceleration.y = 0;
}