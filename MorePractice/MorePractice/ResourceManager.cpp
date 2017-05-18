#include "ResourceManager.h"


ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::LoadResources()
{
	for (unsigned int i = 0; ShaderResources(i) < ShaderResources::NUM_SHADER_RESOURCES; i++)
	{
		m_shaders.AddResource(ShaderResources(i), LoadShader(m_shaderLocations.GetFilePath(ShaderResources(i))));
	}
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