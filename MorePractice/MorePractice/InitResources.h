#pragma once
#include "ResourceManager.h"

void InitResources()
{
	//FONTS
	ResourceManager::getInstance().m_shaderLocations.AddResource(Levels::GLOBAL, ShaderResources::DEFAULT_SPRITE, "triangle.shader");
	ResourceManager::getInstance().m_shaderLocations.AddResource(Levels::GLOBAL, ShaderResources::ARIAL_FONT, "arial.shader");

	//TEXTURES


	ResourceManager::getInstance().LoadResources(Levels::GLOBAL);
}