#include "ResourceManager.h"


ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::LoadResources(Levels a_level)
{
	for (unsigned int i = 0; ShaderResources(i) < ShaderResources::NUM_SHADER_RESOURCES; i++)
	{
		m_shaders.AddResource(a_level, ShaderResources(i), LoadShader(m_shaderLocations.GetFilePath(a_level, ShaderResources(i))));
	}
}

void ResourceManager::UnloadResources(Levels a_level)
{
	m_shaders.RemoveAllResourcesFromLevel(a_level);
}

GLSLProgram&& ResourceManager::LoadShader(std::string a_path)
{
	std::ifstream readMarker(a_path);

	GLSLProgram shader;
	char path[255];

	while (readMarker.getline(path, 255)) {
		switch (path[0])
		{
		case 'v':
			shader.compileShaderFromFile(path + 2, GLSLShaderType::VERTEX);
			break;
		case 'f':
			shader.compileShaderFromFile(path + 2, GLSLShaderType::FRAGMENT);
			break;
		default:
			break;
		}
	}
	shader.link();

	return std::move(shader);
}