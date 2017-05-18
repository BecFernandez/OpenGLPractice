#pragma once
#include "ResourceManager.h"

void InitResources()
{
	ResourceManager::getInstance().m_shaderLocations.AddResource(ShaderResources::DEFAULT_SPRITE, "triangle.shader");
	ResourceManager::getInstance().m_shaderLocations.AddResource(ShaderResources::ARIAL_FONT, "arial.shader");


	ResourceManager::getInstance().LoadResources();
}