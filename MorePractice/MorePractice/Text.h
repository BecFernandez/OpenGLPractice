#ifndef __TEXT_H__
#define __TEXT_H__

#include "Sprite.h"
#include <vector>

struct Character 
{
	int x, y, width, height;
	char value;
};

class Text : public Sprite
{
private:
	std::vector<Character> m_characters;
public:
	Text(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const char* a_szTexName, const char *a_szXMLName);
	void Update(const double a_dDeltaTime);
	void DrawString(const GLuint VBO, const GLuint IBO, GLSLProgram *shader, const char* a_szToDraw);
};

#endif