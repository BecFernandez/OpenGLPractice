#pragma once
#include "Physics.h"
#include "Component.h"

class PhysicsComponent : public Component {
public:
	PhysicsComponent();
	PhysicsComponent(const glm::vec3 a_position, const float a_fRotationSpeed, const float a_fRotationAngle = 0, const float a_fFrictionValue = 0.97f);
	void AddForce(const glm::vec2 a_force) { m_acceleration += a_force; }
	void AddRotation(const float a_fRotation) { m_fRotationAngle += a_fRotation; }
	glm::vec3 GetPosition() const { return m_position; }
	float GetRotation() const { return m_fRotationAngle; }
	void Update(const double a_dDeltaTime);

private:
	glm::vec3 m_position;
	float m_fRotationAngle;

	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	float m_fRotationSpeed;

	float m_fFrictionValue;
};