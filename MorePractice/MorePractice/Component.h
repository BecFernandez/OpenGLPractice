#pragma once

enum ComponentTypes {
	SPRITE,
	PHYSICS,
};

class Component {
public:
	Component(const ComponentTypes a_componentType) : m_componentType(a_componentType) {}
	virtual void Update(const double a_dDeltaTime) = 0;
	ComponentTypes GetComponentType() { return m_componentType; }
private:
	ComponentTypes m_componentType;
};