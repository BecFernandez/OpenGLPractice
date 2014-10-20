#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <GL\glew.h>
#include <GL\glfw.h>
#include "ShaderLoader.h"

struct Vertex
{
	float posx, posy, posz;
	float r, g, b,a;
	float u, v;
};

class Sprite
{
private:
	Vertex corners[4];
	float centrex, centrey, centrez;
	unsigned int texture;
	unsigned int width, height;

public:
	Sprite(float x, float y, float z,
		float r, float g, float b,
		unsigned int width, unsigned int height, const char* texName);
	void Draw(GLuint VBO, GLuint IBO, GLSLProgram *shader);
};

unsigned int LoadTexture(const char * Texture, unsigned int format, 
	unsigned int *width, unsigned int *height, unsigned int *bpp);


#endif