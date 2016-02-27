#pragma once

#include "Component.h"
#include <vector>

class GameObject {
public:
	~GameObject();
	void AddComponent(Component* a_component);
	void RemoveComponent(ComponentTypes a_type);
	Component* GetComponent(ComponentTypes a_type);
	virtual void Update(const double a_dDeltaTime);
private:
	std::vector<Component*> m_components;
};

