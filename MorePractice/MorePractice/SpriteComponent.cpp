#include "SpriteComponent.h"

#include <gtc\matrix_transform.hpp>
#include "GameObject.h"



SpriteComponent::SpriteComponent(const glm::vec4 a_colour, Texture *a_pTexture,
	GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader) : Component(ComponentTypes::SPRITE),
	m_uiVAO(a_uiVAO), m_uiVBO(a_uiVBO), m_uiIBO(a_uiIBO), m_pShader(a_pShader)
{
	for (int i = 0; i < 4; i++)
	{
		m_corners[i].position.z = 0;
		m_corners[i].position.w = 1;
		m_corners[i].colour = a_colour;

		if (i / 2)
		{
			m_corners[i].position.x = m_pTexture->GetWidth() *0.5f * (float)-1;
			m_corners[i].texCoords.s = 0;
		}
		else
		{
			m_corners[i].position.x = m_pTexture->GetWidth()*0.5f;
			m_corners[i].texCoords.s = 1;
		}
		if (i % 3)
		{
			m_corners[i].position.y = m_pTexture->GetHeight()*0.5f;
			m_corners[i].texCoords.t = 1;
		}
		else
		{
			m_corners[i].position.y = m_pTexture->GetHeight()*0.5f * (float)-1;
			m_corners[i].texCoords.t = 0;
		}
	}
}

void SpriteComponent::Init(unsigned int a_uiId, const glm::vec4 a_colour, Texture *a_pTexture,
	GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader)
{
	m_pTexture = a_pTexture;
	m_uiVAO = a_uiVAO;
	m_uiVBO = a_uiVBO;
	m_uiIBO = a_uiIBO;
	m_pShader = a_pShader;
	m_uiID = a_uiId;

	for (int i = 0; i < 4; i++)
	{
		m_corners[i].position.z = 0;
		m_corners[i].position.w = 1;
		m_corners[i].colour = a_colour;

		if (i / 2)
		{
			m_corners[i].position.x = m_pTexture->GetWidth() *0.5f * (float)-1;
			m_corners[i].texCoords.s = 0;
		}
		else
		{
			m_corners[i].position.x = m_pTexture->GetWidth()*0.5f;
			m_corners[i].texCoords.s = 1;
		}
		if (i % 3)
		{
			m_corners[i].position.y = m_pTexture->GetHeight()*0.5f;
			m_corners[i].texCoords.t = 1;
		}
		else
		{
			m_corners[i].position.y = m_pTexture->GetHeight()*0.5f * (float)-1;
			m_corners[i].texCoords.t = 0;
		}
	}
}

void SpriteComponent::UpdateCornersGrounded(unsigned int a_uiWidth, unsigned int a_uiHeight)
{
	for (int i = 0; i < 4; i++)
	{
		if (i / 2)
		{
			m_corners[i].position.x = (float)a_uiWidth *0.5f * (float)-1;
		}
		else
		{
			m_corners[i].position.x = (float)a_uiWidth*0.5f;
		}
		if (i % 3)
		{
			m_corners[i].position.y = (float)a_uiHeight;
		}
		else
		{
			m_corners[i].position.y = 0;
		}
	}
}

void SpriteComponent::Update(double a_dDeltaTime)
{
	
}

void SpriteComponent::Draw() const
{
	//m_pShader->use();
	glBindVertexArray(m_uiVAO);
	//copy vertices to GPU in case they have changed
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	GLvoid *vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(vBuffer, m_corners, sizeof(Vertex) * 4);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);

	glBindTexture(GL_TEXTURE_2D, m_pTexture->GetHandle());

	m_pShader->setUniform("world", m_pGameObject->GetGlobalTransform());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)(sizeof(glm::vec4)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)(sizeof(glm::vec4) * 2));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteComponent::ChangeColour(const glm::vec4 a_NewColour)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_corners[i].colour = a_NewColour;
	}
}

void SpriteComponent::SetSpriteUVCoords(const float a_fUleft, const float a_fVbottom, const float a_fUright, const float a_fVtop)
{
	m_corners[0].texCoords.s = m_corners[1].texCoords.s = a_fUright;
	m_corners[2].texCoords.s = m_corners[3].texCoords.s = a_fUleft;
	m_corners[0].texCoords.t = m_corners[3].texCoords.t = a_fVbottom;
	m_corners[1].texCoords.t = m_corners[2].texCoords.t = a_fVtop;
}