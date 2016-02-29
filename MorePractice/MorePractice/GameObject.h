#pragma once

#include "Component.h"
#include <vector>

class GameObject {
public:
	GameObject();
	~GameObject();
	void AddComponent(Component* a_component);
	void RemoveComponent(ComponentTypes a_type);
	Component* GetComponent(ComponentTypes a_type) const;
	virtual void Update(const double a_dDeltaTime);
	bool IsActive() const { return m_bActive; }
private:
	std::vector<Component*> m_components;

protected:
	bool m_bActive;
};

