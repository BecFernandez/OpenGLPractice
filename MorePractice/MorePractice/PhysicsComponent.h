#pragma once
#include "Physics.h"
#include "Component.h"

class PhysicsComponent : public Component {
public:
	PhysicsComponent();
	PhysicsComponent(const float a_fRotationSpeed, const float a_fFrictionValue = 0.97f);
	void Init(const float a_fRotationSpeed, const float a_fFrictionValue = 0.97f);
	void AddForce(const glm::vec2 a_force) { m_acceleration += a_force; }
	void AddRotation(const float a_fRotation); 
	void Update(const double a_dDeltaTime);

private:
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	float m_fRotationSpeed;

	float m_fFrictionValue;
};