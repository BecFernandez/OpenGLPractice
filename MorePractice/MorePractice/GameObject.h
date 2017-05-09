#pragma once
#include <GL\glew.h>
#include <GL\glfw3.h>
#include <map>
#include <glm.hpp>

#include "Component.h"
#include "Subject.h"
#include "ComponentPoolHelper.h"

//template <typename T>
class GameObject : public Subject
{
public:
	GameObject();
	GameObject(ComponentPoolHelper* a_pComponentPoolHelper, glm::vec3 a_position = glm::vec3(0.0, 0.0, 0.0), float a_fRotationAngle = 0, float a_fScale = 1);
	~GameObject();
	void AddComponent(ComponentTypes a_type, unsigned int a_id);
	void RemoveComponent(ComponentTypes a_type);
	Component* GetComponent(ComponentTypes a_type);
	virtual void Update(const double a_dDeltaTime);
	bool IsActive() const { return m_bActive; }
	glm::mat4 GetGlobalTransform();
	void ResetComponentPointers();
	void ClearComponentsList() { m_components.clear(); }

	glm::vec3 m_position;
	float m_fScale;
	float m_fRotationAngle;
	virtual void SetActive(bool a_bValue);

private:
	std::map<ComponentTypes, unsigned int> m_components;
	glm::mat4 m_globalTransform;

protected:
	bool m_bActive;
	ComponentPoolHelper* m_pComponentPoolHelper;
};

