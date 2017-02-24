#pragma once

#include <map>
#include <glm.hpp>

#include "Component.h"
#include "Subject.h"
#include "ComponentPool.h"

//template <typename T>
class GameObject : public Subject
{
public:
	GameObject();
	GameObject(glm::vec3 a_position, float a_fRotationAngle = 0, float a_fScale = 1);
	~GameObject();
	template <typename T>
	void AddComponent(ComponentTypes a_type, ObjectPool<T> *a_pComponentPool, unsigned int a_id);
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
	template <typename T>
	std::map<ComponentTypes, ObjectPool<T>*> m_componentPoolLinks;
	std::map<ComponentTypes, unsigned int> m_components;
	glm::mat4 m_globalTransform;

protected:
	bool m_bActive;
};

