#include "ComponentPoolHelper.h"


ComponentPoolHelper::ComponentPoolHelper()
{
	//init all the pools
	m_physicsComponentPool = nullptr;
	m_spriteComponentPool = nullptr;
	m_colliderComponentPool = nullptr;
	m_healthComponentPool = nullptr;
}

ComponentPoolHelper::~ComponentPoolHelper()
{
	if (m_physicsComponentPool != nullptr) {
		delete m_physicsComponentPool;
	}
	if (m_spriteComponentPool != nullptr) {
		delete m_spriteComponentPool;
	}
	if (m_colliderComponentPool != nullptr) {
		delete m_colliderComponentPool;
	}
	if (m_healthComponentPool != nullptr) {
		delete m_healthComponentPool;
	}
}

void ComponentPoolHelper::Update(const double a_dDeltaTime)
{
	if (m_physicsComponentPool != nullptr)
	{
		m_physicsComponentPool->Update(a_dDeltaTime);
	}
	if (m_spriteComponentPool != nullptr)
	{
		m_spriteComponentPool->Update(a_dDeltaTime);
	}
	if (m_colliderComponentPool != nullptr)
	{
		m_colliderComponentPool->Update(a_dDeltaTime);
	}
	if (m_healthComponentPool != nullptr)
	{
		m_healthComponentPool->Update(a_dDeltaTime);
	}
}

Component* ComponentPoolHelper::GetComponent(ComponentTypes a_type, unsigned int a_uiComponentID)
{
	switch (a_type)
	{
	case ComponentTypes::COLLIDER:
		if (m_colliderComponentPool != nullptr) {
			return m_colliderComponentPool->GetObjectById(a_uiComponentID);
		}
		break;
	case ComponentTypes::HEALTH:
		if (m_healthComponentPool != nullptr) {
			return m_healthComponentPool->GetObjectById(a_uiComponentID);
		}
		break;
	case ComponentTypes::PHYSICS:
		if (m_physicsComponentPool != nullptr) {
			return m_physicsComponentPool->GetObjectById(a_uiComponentID);
		}
		break;
	case ComponentTypes::SPRITE:
		if (m_spriteComponentPool != nullptr) {
			return m_spriteComponentPool->GetObjectById(a_uiComponentID);
		}
		break;
	}
	return nullptr;
}

void ComponentPoolHelper::DestroyComponent(ComponentTypes a_type, unsigned int a_uiComponentID)
{
	switch (a_type)
	{
	case ComponentTypes::COLLIDER:
		if (m_colliderComponentPool != nullptr) {
			m_colliderComponentPool->Destroy(a_uiComponentID);
		}
		break;
	case ComponentTypes::HEALTH:
		if (m_healthComponentPool != nullptr) {
			m_healthComponentPool->Destroy(a_uiComponentID);
		}
		break;
	case ComponentTypes::PHYSICS:
		if (m_physicsComponentPool != nullptr) {
			m_physicsComponentPool->Destroy(a_uiComponentID);
		}
		break;
	case ComponentTypes::SPRITE:
		if (m_spriteComponentPool != nullptr) {
			m_spriteComponentPool->Destroy(a_uiComponentID);
		}
		break;
	}
}