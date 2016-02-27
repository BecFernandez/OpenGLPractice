#pragma once
#include "Physics.h"
#include "Component.h"

class PhysicsComponent : public Component {
public:
	PhysicsComponent();
	PhysicsComponent(const glm::vec3 a_position, const float a_fRotationSpeed, const float a_fRotationAngle = 0);
	void AddForce(const glm::vec2 a_force);
	void AddRotation(const float a_fRotation);
	void Update(const double a_dDeltaTime);
	glm::vec3 GetPosition() const { return m_position; }
	float GetRotation() const { return m_fRotationAngle; }

private:
	glm::vec3 m_position;
	float m_fRotationAngle;

	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	float m_fRotationSpeed;

	static const float m_fFrictionValue;
};