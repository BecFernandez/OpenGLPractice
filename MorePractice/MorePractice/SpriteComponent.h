#pragma once

#include "Component.h"
#include "ShaderLoader.h"
#include "Vertex.h"
#include "Texture.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent() : Component(ComponentTypes::SPRITE) {}
	SpriteComponent(const glm::vec4 a_colour, Texture *a_pTexture,
		GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader);
	void Init(unsigned int a_uiId, const glm::vec4 a_colour, Texture *a_pTexture,
		GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader);
	void UpdateCornersGrounded(unsigned int a_uiWidth, unsigned int a_uiHeight);
	void Update(const double a_dDeltaTime);
	void Draw() const;
	void ChangeColour(const glm::vec4 a_NewColour);
	void SetSpriteUVCoords(const float a_fULeft, const float a_fVbottom, const float a_fUright, const float a_fVtop);

protected:
	Texture *m_pTexture;

private:
	Vertex m_corners[4]; //all my sprites are rectangles
	GLuint m_uiVAO;
	GLuint m_uiVBO;
	GLuint m_uiIBO;
	const GLSLProgram *m_pShader;
};