#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <GL\glew.h>
#include <GL\glfw3.h>
#include "ShaderLoader.h"
#include "Physics.h"

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
	float m_fRotationAngle;
	glm::vec2 m_oVelocity;
	glm::vec2 m_oAcceleration;

public:
	Sprite();
	Sprite(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const char* a_szTexName);
	void InitSprite(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned const int a_uiHeight, const char* a_szTexName);
	void InitSprite(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const unsigned int a_uiTexture);
	glm::vec3 getCentrePos() const;
	float getRotationAngle() const;
	virtual void Draw(const GLuint VBO, const GLuint IBO, GLSLProgram *shader) const;
	//will change this to take in delta time
	virtual void Update(const double a_dDeltaTime);
	AABB getAABB() const;
	void changeColour(const glm::vec4 a_oNewColour);
	void setSpriteUVCoords(const float a_fUleft, const float a_fVbottom, const float a_fUright, const float a_iVtop);
};

unsigned int LoadTexture(const char * Texture, const unsigned int format, 
	unsigned int *width, unsigned int *height, unsigned int *bpp);


#endif