#pragma once
#include "ResourceManager.h"

void InitResources()
{
	ResourceManager& resourceManager = ResourceManager::getInstance();

	//SHADERS
	resourceManager.m_shaderLocations.AddResource(Levels::GLOBAL, ShaderResources::DEFAULT_SPRITE, "triangle.shader");
	resourceManager.m_shaderLocations.AddResource(Levels::GLOBAL, ShaderResources::ARIAL_FONT, "arial.shader");

	//TEXTURES
	resourceManager.m_textureLocations.AddResource(Levels::GLOBAL, TextureResources::ARIAL_0, "arial_0.png");
	resourceManager.m_textureLocations.AddResource(Levels::MAIN_SCREEN, TextureResources::SPACE_WARS, "SpaceWars.jpg");
	resourceManager.m_textureLocations.AddResource(Levels::GAME_SCREEN, TextureResources::SHIP, "ship.png");
	resourceManager.m_textureLocations.AddResource(Levels::GAME_SCREEN, TextureResources::CYLON, "cylon.png");
	resourceManager.m_textureLocations.AddResource(Levels::GAME_SCREEN, TextureResources::LASER, "laser.png");
	resourceManager.m_textureLocations.AddResource(Levels::LOSE_SCREEN, TextureResources::EXPLOSION, "explosion.jpg");
	resourceManager.m_textureLocations.AddResource(Levels::WIN_SCREEN, TextureResources::FIREWORKS, "fireworks.jpg");

	//FONTS
	resourceManager.m_fontLocations.AddResource(Levels::GLOBAL, FontResources::ARIAL_0, "arial.fnt");

	resourceManager.LoadResources(Levels::GLOBAL);
}

void RemoveGlobalResources()
{
	ResourceManager::getInstance().UnloadResources(Levels::GLOBAL);
}