#pragma once

#include <vector>
#include "Physics.h"
#include "ComponentPool.h"
#include "ComponentPoolHelper.h"

class PhysicsManager
{
public:
	PhysicsManager(ComponentPoolHelper *a_pComponentPoolHelper);
	void Update();

private:
	ComponentPoolHelper *m_pComponentPoolHelper;
};