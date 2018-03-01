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
		std::string shaderPath = m_shaderLocations.GetFilePath(a_level, ShaderResources(i));
		if (!shaderPath.empty())
		{
			m_shaders.AddResource(a_level, ShaderResources(i), LoadShader(shaderPath.c_str()));
		}
	}

	for (unsigned int i = 0; TextureResources(i) < TextureResources::NUM_TEXTURE_RESOURCES; i++)
	{
		std::string texturePath = m_textureLocations.GetFilePath(a_level, TextureResources(i));
		if (!texturePath.empty())
		{
			m_textures.AddResource(a_level, TextureResources(i), Texture(texturePath.c_str()));
		}
	}

	for (unsigned int i = 0; FontResources(i) < FontResources::NUM_FONT_RESOURCES; i++)
	{
		std::string fontPath = m_fontLocations.GetFilePath(a_level, FontResources(i));
		if (!fontPath.empty())
		{
			m_fonts.AddResource(a_level, FontResources(i), LoadCharacters(fontPath.c_str()));
		}
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