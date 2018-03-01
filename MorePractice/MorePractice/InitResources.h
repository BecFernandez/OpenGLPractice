#pragma once
#include "ResourceManager.h"

void InitResources()
{
	//SHADERS
	ResourceManager::getInstance().m_shaderLocations.AddResource(Levels::GLOBAL, ShaderResources::DEFAULT_SPRITE, "triangle.shader");
	ResourceManager::getInstance().m_shaderLocations.AddResource(Levels::GLOBAL, ShaderResources::ARIAL_FONT, "arial.shader");

	//TEXTURES
	ResourceManager::getInstance().m_textureLocations.AddResource(Levels::GLOBAL, TextureResources::ARIAL_0, "arial_0.png");
	ResourceManager::getInstance().m_textureLocations.AddResource(Levels::MAIN_SCREEN, TextureResources::SPACE_WARS, "SpaceWars.jpg");
	ResourceManager::getInstance().m_textureLocations.AddResource(Levels::GAME_SCREEN, TextureResources::SHIP, "ship.png");
	ResourceManager::getInstance().m_textureLocations.AddResource(Levels::GAME_SCREEN, TextureResources::CYLON, "cylon.png");
	ResourceManager::getInstance().m_textureLocations.AddResource(Levels::GAME_SCREEN, TextureResources::LASER, "laser.png");
	ResourceManager::getInstance().m_textureLocations.AddResource(Levels::LOSE_SCREEN, TextureResources::EXPLOSION, "explosion.jpg");
	ResourceManager::getInstance().m_textureLocations.AddResource(Levels::WIN_SCREEN, TextureResources::FIREWORKS, "fireworks.jpg");

	//FONTS
	ResourceManager::getInstance().m_fontLocations.AddResource(Levels::GLOBAL, FontResources::ARIAL_0, "arial.fnt");

	ResourceManager::getInstance().LoadResources(Levels::GLOBAL);
}