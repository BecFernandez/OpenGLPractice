#pragma once

#include "Component.h"

class HealthComponent : public Component
{
public:
	HealthComponent();
	void Init(unsigned int a_uiId, const int a_iHealth);
	void TakeDamage(const int a_iDamage) { m_iHealth -= a_iDamage; }
	bool IsAlive() const { return m_iHealth > 0; }
	void Update(const double a_dDeltaTime) {}
	float HealthRatio() { return (float)m_iHealth / (float)m_iMaxHealth; }
private:
	int m_iHealth;
	int m_iMaxHealth;
	unsigned int m_uiId;
};