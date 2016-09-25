#pragma once
class GameObject;

enum ComponentTypes {
	SPRITE,
	PHYSICS,
	HEALTH,
	COLLIDER
};

class Component {
public:
	Component(const ComponentTypes a_componentType, bool a_bActive = false) : m_componentType(a_componentType), m_bActive(a_bActive) {}
	virtual void Update(const double a_dDeltaTime) = 0;
	ComponentTypes GetComponentType() const { return m_componentType; }
	void SetGameObject(GameObject* a_pGameObject) { m_pGameObject = a_pGameObject; }
private:
	ComponentTypes m_componentType;

protected:
	

public:
	bool m_bActive;
	//keep a reference to the game object that owns this component. That means we can access the position, rotation, scale from any component.
	GameObject *m_pGameObject;
};