#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <GL\glew.h>
#include <GL\glfw.h>
#include "ShaderLoader.h"

struct Vertex
{
	glm::vec4 position; 
	glm::vec4 colour;
	glm::vec2 texCoords;
};

class Sprite
{
private:
	Vertex m_corners[4]; //all my sprites are rectangles
	unsigned int m_uiTexture;
	unsigned int m_uiWidth, m_uiHeight;
	glm::mat4 m_globalTransform;
	
protected:
	glm::vec3 m_oCentrePos;

public:
	Sprite(glm::vec3 a_position,
		glm::vec4 a_colour,
		unsigned int a_uiWidth, unsigned int a_uiHeight, const char* a_szTexName);
	void Draw(GLuint VBO, GLuint IBO, GLSLProgram *shader);
	//will change this to take in delta time
	void Update();
};

unsigned int LoadTexture(const char * Texture, unsigned int format, 
	unsigned int *width, unsigned int *height, unsigned int *bpp);


#endif

/*
OK, let's change this up so we're using matrices to place and move everything around.
So I need a camera matrix for the world, a view matrix for the world, and a global matrix for each object


*/