#pragma once
#include "Physics.h"
#include "Component.h"

class PhysicsComponent : public Component {
public:
	PhysicsComponent();
	PhysicsComponent(const glm::vec3 a_position, const float a_fRotationSpeed, const float a_fRotationAngle = 0, const float a_fFrictionValue = 0.97f, bool a_bActive = true);
	void AddForce(const glm::vec2 a_force) { m_acceleration += a_force; }
	void AddRotation(const float a_fRotation) { m_fRotationAngle += a_fRotation; }
	void Update(const double a_dDeltaTime);

	//these are going to have to be public - I need to get and set them from the bullet object
	glm::vec3 m_position;
	float m_fRotationAngle;

private:
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	float m_fRotationSpeed;

	float m_fFrictionValue;
};