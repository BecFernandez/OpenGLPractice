#pragma once
class GameObject;

enum class ComponentTypes {
	SPRITE,
	PHYSICS,
	HEALTH,
	COLLIDER,
	TEXT,
	NUM_COMPONENTS
};

class Component {
public:
	Component(const ComponentTypes a_componentType) : m_componentType(a_componentType) {}
	virtual void Update(const double a_dDeltaTime) = 0;
	ComponentTypes GetComponentType() const { return m_componentType; }
	void SetGameObject(GameObject* a_pGameObject) { m_pGameObject = a_pGameObject; }
	unsigned int GetID() { return m_uiID; }
	void PostMoveUpdate() {}

private:
	ComponentTypes m_componentType;

protected:
	unsigned int m_uiID;

public:
	//keep a reference to the game object that owns this component. That means we can access the position, rotation, scale from any component.
	GameObject *m_pGameObject;
};