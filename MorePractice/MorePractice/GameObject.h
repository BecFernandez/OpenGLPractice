#pragma once

#include <vector>
#include <glm.hpp>

#include "Component.h"
#include "Subject.h"

class GameObject : public Subject
{
public:
	GameObject();
	GameObject(glm::vec3 a_position, float a_fRotationAngle = 0, float a_fScale = 1);
	~GameObject();
	void AddComponent(Component* a_component);
	void RemoveComponent(ComponentTypes a_type);
	Component* GetComponent(ComponentTypes a_type) const;
	virtual void Update(const double a_dDeltaTime);
	bool IsActive() const { return m_bActive; }
	glm::mat4 GetGlobalTransform();

	glm::vec3 m_position;
	float m_fScale;
	float m_fRotationAngle;
	virtual void SetActive(bool a_bValue);

private:
	std::vector<Component*> m_components;
	glm::mat4 m_globalTransform;

protected:
	bool m_bActive;
	virtual void setComponentPointers() {}
};

