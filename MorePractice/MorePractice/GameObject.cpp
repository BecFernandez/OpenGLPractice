#include "GameObject.h"
#include <iostream>
#include <gtc\matrix_transform.hpp>


GameObject::GameObject() : m_bActive(false), m_fRotationAngle(0), m_fScale(1), m_position(glm::vec3())
{

}

GameObject::GameObject(glm::vec3 a_position, float a_fRotationAngle, float a_fScale) : m_fRotationAngle(a_fRotationAngle), m_fScale(a_fScale), m_position(a_position), m_bActive(false)
{
	
}

GameObject::~GameObject()
{
	/*for (int i = 0; i < m_components.size(); i++) {
		delete m_components[i];
	}*/

	m_components.clear();
}

void GameObject::AddComponent(Component* a_component)
{
	m_components.push_back(a_component);
	a_component->SetGameObject(this);
	setComponentPointers();
}

//This could definitely be done better. I want to take performance into account a little bit - so I would like to find out:
// 1. Is a vector the correct data structure for this? (I know vectors perform well for iteration, but slowly for removals + resizing. I am doing a lot of iteration though...)
// 2. Should I be using this vector? Should I roll my own? Or should I try using the EASTL since they've just released it? (I'm leaning towards the last option since it would be a good idea to 
//    see how they have implemented it).
void GameObject::RemoveComponent(ComponentTypes a_type)
{
	int indexToErase;

	for (int i = 0; i < m_components.size(); i++) {
		if (m_components[i]->GetComponentType() == a_type) {
			indexToErase = i;
			break;
		}
	}

	m_components.erase(m_components.begin() + indexToErase);
}

Component* GameObject::GetComponent(ComponentTypes a_type) const {
	for (int i = 0; i < m_components.size(); i++) {
		if (m_components[i]->GetComponentType() == a_type) {
			return m_components[i];
		}
	}
	return nullptr;
}

void GameObject::Update(const double a_dDeltaTime)
{
	m_globalTransform = glm::translate(glm::mat4(1), glm::vec3(m_position.x, m_position.y, m_position.z)) *
		glm::rotate(glm::mat4(1), m_fRotationAngle, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(m_fScale, m_fScale, 1));
}

glm::mat4 GameObject::GetGlobalTransform()
{
	return m_globalTransform;
}

void GameObject::SetActive(bool a_bValue)
{
	if (m_bActive != a_bValue) {
		m_bActive = a_bValue;
	}
}