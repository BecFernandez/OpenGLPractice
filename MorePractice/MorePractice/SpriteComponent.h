#pragma once

#include "Component.h"
#include "Sprite.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(const glm::vec4 a_colour,
		const glm::vec2 a_dimensions, const char* a_szTexName,
		GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram* a_pShader);

	void UpdateCornersGrounded(unsigned int a_uiWidth, unsigned int a_uiHeight);
	void Update(glm::vec3 a_position, float a_fRotationAngle, float a_fScale);
	void Draw() const;
	void ChangeColour(const glm::vec4 a_NewColour);
	void SetSpriteUVCoords(const float a_fULeft, const float a_fVbottom, const float a_fUright, const float a_fVtop);

private:
	Vertex m_corners[4]; //all my sprites are rectangles
	unsigned int m_uiTexture;
	glm::mat4 m_globalTransform;
	glm::vec2 m_dimensions;
	glm::vec2 m_textureDimensions;
	GLuint m_uiVBO;
	GLuint m_uiIBO;
	GLSLProgram *m_pShader;
};