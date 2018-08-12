#pragma once
#include "ResourceEnums.h"
#include "ResourceStorage.h"
#include "ResourceLocationMap.h"
#include "ShaderLoader.h"
#include "Texture.h"
#include "FontComponent.h"

class ResourceManager
{
public:
	static ResourceManager& getInstance();

	ResourceStorage<ShaderResources, GLSLProgram*> m_shaders;
	ResourceLocationMap<ShaderResources> m_shaderLocations;

	ResourceStorage < TextureResources, Texture*> m_textures;
	ResourceLocationMap<TextureResources> m_textureLocations;

	ResourceStorage<FontResources, std::map<char, Character>*> m_fonts;
	ResourceLocationMap<FontResources> m_fontLocations;

	void LoadResources(Levels a_level); 
	void UnloadResources(Levels a_level);

private:
	ResourceManager() {}
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;
};
