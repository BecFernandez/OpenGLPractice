#pragma once

enum ComponentTypes {
	SPRITE,
	PHYSICS,
	HEALTH
};

class Component {
public:
	Component(const ComponentTypes a_componentType, bool a_bActive = true) : m_componentType(a_componentType), m_bActive(a_bActive) {}
	virtual void Update(const double a_dDeltaTime) = 0;
	ComponentTypes GetComponentType() const { return m_componentType; }
private:
	ComponentTypes m_componentType;
	//think I'm going to have to have an enabled boolean here since the bullets are pooled. They will be created but inactive, which means they shouldn't draw or collide.
public:
	bool m_bActive;
};