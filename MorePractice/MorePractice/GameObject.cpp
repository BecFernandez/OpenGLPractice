#include "GameObject.h"
#include <iostream>
#include <gtc\matrix_transform.hpp>
#include <vector>


GameObject::GameObject() : m_pComponentPoolHelper(nullptr), m_bActive(false), m_fRotationAngle(0), m_fScale(1), m_position(glm::vec3())
{

}

GameObject::GameObject(ComponentPoolHelper *a_pComponentPoolHelper, glm::vec3 a_position, float a_fRotationAngle, float a_fScale) : 
	m_pComponentPoolHelper(a_pComponentPoolHelper), m_fRotationAngle(a_fRotationAngle), m_fScale(a_fScale), m_position(a_position), m_bActive(false)
{
	
}

GameObject::~GameObject()
{
	std::vector<ComponentTypes> componentTypesToDelete;
	for (std::map<ComponentTypes, unsigned int>::iterator it = m_components.begin(); it != m_components.end(); it++) {
		componentTypesToDelete.push_back(it->first);
	}

	for (unsigned int i = 0; i < componentTypesToDelete.size(); i++) {
		RemoveComponent(componentTypesToDelete[i]);
	}

	m_components.clear();
}

void GameObject::AddComponent(ComponentTypes a_type, unsigned int a_id)
{
	if (m_components.find(a_type) == m_components.end()) {
		m_components[a_type] = a_id;
		Component* a_component = GetComponent(a_type);
		a_component->SetGameObject(this);
	}
	else {
		//TODO - add custom assert code so I can add useful error messages
		assert(true);
	}

	//Issue - the way I have this set up now it is possible for someone to call this function twice with the same component ID (and type) but different game objects
	//this is bad. The first game object will still think it owns the component while the component will have the second game object set as it's owner.
	//Perhaps I should set up the AddComponent to create the component within this function. I'd need to pass all the variables through for initialisation.
	//Urgent TODO.
}

void GameObject::ResetComponentPointers()
{
	for (std::map<ComponentTypes, unsigned int>::iterator it = m_components.begin(); it != m_components.end(); it++) {
		Component* component = GetComponent(it->first);
		if (component != nullptr) {
			component->SetGameObject(this);
		}
		else {
			std::cout << "GameObject being reset has no " << (int)it->first << "component" << std::endl;
		}
	}
}

void GameObject::RemoveComponent(ComponentTypes a_type)
{
	if (m_components.find(a_type) != m_components.end()) {

		//should I be removing it from the pool here too?
		//I think so - and once the above TODO is fixed then this shouldn't cause any other issues since this game object will be the only owner of the component
		m_pComponentPoolHelper->DestroyComponent(a_type, m_components[a_type]);
		m_components.erase(a_type);
	}
	else {
		//should probably have a warning or something happen here
	}

}

Component* GameObject::GetComponent(ComponentTypes a_type) {
	if (m_components.find(a_type) != m_components.end()) {
		return m_pComponentPoolHelper->GetComponent(a_type, m_components[a_type]);
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