#pragma once
#include "ResourceEnums.h"
#include "ResourceStorage.h"
#include "ResourceLocationMap.h"
#include "ShaderLoader.h"

#include <fstream>

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	ResourceStorage<ShaderResources, GLSLProgram> m_shaders;
	ResourceLocationMap<ShaderResources> m_shaderLocations;

	void LoadResources(); //TODO - separate resources into levels so we can load and unload them when it makes sense?

private:
	ResourceManager() {}
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;
	//maybe it makes more sense to have these as static functions in more related classes?
	GLSLProgram&& LoadShader(std::string a_path);
};
