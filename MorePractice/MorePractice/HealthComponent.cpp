#include "HealthComponent.h"

HealthComponent::HealthComponent() : Component(ComponentTypes::HEALTH), m_iHealth(0), m_iMaxHealth(0)
{

}

void HealthComponent::Init(unsigned int a_uiId, const int a_iHealth)
{
	m_uiID = a_uiId;
	m_iHealth = a_iHealth;
	m_iMaxHealth = a_iHealth;
}