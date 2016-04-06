#pragma once

#include "Component.h"

class HealthComponent : public Component
{
public:
	HealthComponent(const int a_iHealth);
	void TakeDamage(const int a_iDamage) { m_iHealth -= a_iDamage; }
	bool IsAlive() const { return m_iHealth > 0; }
	void Update(const double a_dDeltaTime) {}
private:
	int m_iHealth;
};