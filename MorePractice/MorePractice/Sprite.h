#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <GL\glew.h>
#include <GL\glfw3.h>
#include "ShaderLoader.h"
#include "Physics.h"

void checkGLError(const char* customMessage);

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
	glm::mat4 m_globalTransform;
	
protected:
	unsigned int m_uiWidth, m_uiHeight;
	glm::vec3 m_oCentrePos;
	float m_fRotationAngle;
	float m_fScale;

	glm::vec2 m_oVelocity;
	glm::vec2 m_oAcceleration;

	unsigned int m_uiTextureWidth;
	unsigned int m_uiTextureHeight;
	void changeColour(const glm::vec4 a_oNewColour);

public:
	Sprite();
	Sprite(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const char* a_szTexName);
	void InitSprite(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const char* a_szTexName);
	void InitSprite(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const unsigned int a_uiTexture);
	glm::vec3 getCentrePos() const;
	float getRotationAngle() const;
	virtual void Draw(const GLuint VBO, const GLuint IBO, GLSLProgram *shader) const;
	//will change this to take in delta time
	virtual void Update(const double a_dDeltaTime);
	void UpdateCorners(unsigned int a_uiWidth, unsigned int a_uiHeight);
	void UpdateCornersGrounded(unsigned int a_uiWidth, unsigned int a_uiHeight);
	AABB getAABB() const;
	void setSpriteUVCoords(const float a_fUleft, const float a_fVbottom, const float a_fUright, const float a_iVtop);
};

unsigned int LoadTexture(const char * Texture, const unsigned int format, 
	unsigned int *width, unsigned int *height, unsigned int *bpp);


#endif