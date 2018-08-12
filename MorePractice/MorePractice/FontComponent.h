#pragma once
#include "SpriteComponent.h"
#include <map>

struct Character
{
	int m_iX, m_iY, m_iWidth, m_iHeight;
	char m_cValue;
};

class FontComponent :
	public SpriteComponent
{

private:
	std::map<char, Character> *m_characters;

public:
	FontComponent();
	~FontComponent();
	void Init(unsigned int a_uiId, const glm::vec4 a_colour,
		Texture *a_pTexture, std::map<char, Character> *a_characters,
		GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader);
	void Draw(const char* a_szToDraw, glm::vec3 a_position, glm::vec4 a_colour = glm::vec4(1.0, 1.0, 1.0, 1.0));
};

std::map<char, Character> *LoadCharacters(const char* a_szXMLName);

