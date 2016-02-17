#pragma once

enum ComponentTypes {
	RENDERER,
	PHYSICS,
};

class Component {
public:
	virtual void Update() = 0;
	ComponentTypes GetComponentType() { return m_componentType; }
private:
	ComponentTypes m_componentType;
};