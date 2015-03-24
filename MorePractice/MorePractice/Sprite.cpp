#include "Sprite.h"
#include <FreeImage.h>
#include <iostream>
#include <gtc\matrix_transform.hpp>

unsigned int LoadTexture(const char * Texture, const unsigned int format, unsigned int* width, unsigned int* height, unsigned int *bpp)
{
	FIBITMAP* bitmap = NULL;

	//check the file format signature, deduce its format and load it
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(Texture, 0);

	if(fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif))
	{
		bitmap = FreeImage_Load(fif, Texture);
	}

	if(bitmap == NULL)
	{
		std::cerr << "Error: Failed to load image " << Texture << std::endl;
		return 0;
	}

	if(width != NULL)
		*width = FreeImage_GetWidth(bitmap);
	if(height != NULL)
		*height = FreeImage_GetHeight(bitmap);

	//force image to RGBA - might change this
	unsigned int BitsPerPixel = FreeImage_GetBPP(bitmap);
	if(bpp != NULL)
		*bpp = BitsPerPixel/8;

	FREE_IMAGE_COLOR_TYPE fiColourType = FreeImage_GetColorType(bitmap);
	if(fiColourType != FIC_RGBALPHA)
	{
		FIBITMAP* ndib = FreeImage_ConvertTo32Bits(bitmap);
		FreeImage_Unload(bitmap);
		bitmap = ndib;
		BitsPerPixel = FreeImage_GetBPP(bitmap);
		fiColourType = FreeImage_GetColorType(bitmap);
	}

	BYTE *data = FreeImage_GetBits(bitmap);

	FREE_IMAGE_TYPE fit = FreeImage_GetImageType(bitmap);
	GLenum eType = (fit == FIT_RGBF || fit == FIT_FLOAT)? GL_FLOAT: GL_UNSIGNED_BYTE; 

	//create texture, finally
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, format, eType, data);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//what is difference between clamp to border and clamp to edge?
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
	FreeImage_Unload(bitmap);

	return texID;
}

Sprite::Sprite() : m_oCentrePos(glm::vec3(0, 0, 0)), m_uiWidth(0), m_uiHeight(0),  m_fRotationAngle(0), m_oVelocity(glm::vec2(0, 0)),
		m_oAcceleration(glm::vec2(0, 0)), m_uiTexture(0)
{

}

Sprite::Sprite(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const char* a_szTexName) 
		: m_oCentrePos(a_position), m_uiWidth(a_uiWidth), m_uiHeight(a_uiHeight), m_fRotationAngle(0), m_oVelocity(glm::vec2(0, 0)),
		m_oAcceleration(glm::vec2(0, 0))
{
	if(a_szTexName != nullptr)
		m_uiTexture = LoadTexture(a_szTexName, GL_RGBA, &m_uiTextureWidth, &m_uiTextureHeight, NULL);  
	else
		m_uiTexture = 0;

	//set up four corners 
	//
	//also setting up texture coords
	for(int i = 0; i < 4; i++)
	{
		m_corners[i].position.z = 0;
		m_corners[i].position.w = 1;
		m_corners[i].colour = a_colour;

		if(i/2)
		{
			m_corners[i].position.x =  (float)m_uiWidth *0.5f * (float)-1;
			m_corners[i].texCoords.s = 0;
		}
		else
		{
			m_corners[i].position.x = (float)m_uiWidth*0.5f;
			m_corners[i].texCoords.s = 1;
		}
		if(i%3)
		{
			m_corners[i].position.y = (float)m_uiHeight*0.5f;
			m_corners[i].texCoords.t = 1;
		}
		else
		{
			m_corners[i].position.y = (float)m_uiHeight*0.5f * (float)-1;
			m_corners[i].texCoords.t = 0;
		}
	}
}

void Sprite::InitSprite(const glm::vec3 a_position, const glm::vec4 a_colour, 
	const unsigned int a_uiWidth, const unsigned int a_uiHeight, const char* a_szTexName)
{
	m_oCentrePos = a_position;
	m_uiWidth = a_uiWidth;
	m_uiHeight = a_uiHeight;

	if(a_szTexName != nullptr)
		m_uiTexture = LoadTexture(a_szTexName, GL_RGBA, NULL, NULL, NULL);  
	else
		m_uiTexture = 0;

	//set up four corners 
	//
	//also setting up texture coords
	for(int i = 0; i < 4; i++)
	{
		m_corners[i].position.z = 0;
		m_corners[i].position.w = 1;
		m_corners[i].colour = a_colour;

		if(i/2)
		{
			m_corners[i].position.x =  (float)m_uiWidth *0.5f * (float)-1;
			m_corners[i].texCoords.s = 0;
		}
		else
		{
			m_corners[i].position.x = (float)m_uiWidth*0.5f;
			m_corners[i].texCoords.s = 1;
		}
		if(i%3)
		{
			m_corners[i].position.y = (float)m_uiHeight*0.5f;
			m_corners[i].texCoords.t = 1;
		}
		else
		{
			m_corners[i].position.y = (float)m_uiHeight*0.5f * (float)-1;
			m_corners[i].texCoords.t = 0;
		}
	}
}

void Sprite::InitSprite(const glm::vec3 a_position, const glm::vec4 a_colour, 
	const unsigned int a_uiWidth, const unsigned int a_uiHeight, const unsigned int a_uiTexture)
{
	m_oCentrePos = a_position;
	m_uiWidth = a_uiWidth;
	m_uiHeight = a_uiHeight;

	m_uiTexture = a_uiTexture;

	//set up four corners 
	//
	//also setting up texture coords
	for(int i = 0; i < 4; i++)
	{
		m_corners[i].position.z = 0;
		m_corners[i].position.w = 1;
		m_corners[i].colour = a_colour;

		if(i/2)
		{
			m_corners[i].position.x =  (float)m_uiWidth *0.5f * (float)-1;
			m_corners[i].texCoords.s = 0;
		}
		else
		{
			m_corners[i].position.x = (float)m_uiWidth*0.5f;
			m_corners[i].texCoords.s = 1;
		}
		if(i%3)
		{
			m_corners[i].position.y = (float)m_uiHeight*0.5f;
			m_corners[i].texCoords.t = 1;
		}
		else
		{
			m_corners[i].position.y = (float)m_uiHeight*0.5f * (float)-1;
			m_corners[i].texCoords.t = 0;
		}
	}
}

void Sprite::UpdateCorners(unsigned int a_uiWidth, unsigned int a_uiHeight)
{
	for(int i = 0; i < 4; i++)
	{
		if(i/2)
		{
			m_corners[i].position.x =  (float)a_uiWidth *0.5f * (float)-1;
		}
		else
		{
			m_corners[i].position.x = (float)a_uiWidth*0.5f;
		}
		if(i%3)
		{
			m_corners[i].position.y = (float)a_uiHeight*0.5f;
		}
		else
		{
			m_corners[i].position.y = (float)a_uiHeight*0.5 * (float)-1;
		}
	}
}

void Sprite::UpdateCornersGrounded(unsigned int a_uiWidth, unsigned int a_uiHeight)
{
	for(int i = 0; i < 4; i++)
	{
		if(i/2)
		{
			m_corners[i].position.x =  (float)a_uiWidth *0.5f * (float)-1;
		}
		else
		{
			m_corners[i].position.x = (float)a_uiWidth*0.5f;
		}
		if(i%3)
		{
			m_corners[i].position.y = (float)a_uiHeight;
		}
		else
		{
			m_corners[i].position.y = 0;
		}
	}
}

glm::vec3 Sprite::getCentrePos() const
{
	return m_oCentrePos;
}

float Sprite::getRotationAngle() const
{
	return m_fRotationAngle;
}

void Sprite::Update(const double a_dDeltaTime)
{
	//wrap sprite around the screen when they move off
	if(m_oCentrePos.x < 0)
		m_oCentrePos.x = 800;
	else if(m_oCentrePos.x > 800)
		m_oCentrePos.x = 0;
	if(m_oCentrePos.y < 0)
		m_oCentrePos.y = 600;
	else if(m_oCentrePos.y > 600)
		m_oCentrePos.y = 0;


	//so in here I really just need to modify the world matrix
	m_globalTransform = glm::translate(glm::mat4(1), glm::vec3(m_oCentrePos.x, m_oCentrePos.y, m_oCentrePos.z)) *
		glm::rotate(glm::mat4(1), m_fRotationAngle, glm::vec3(0, 0, 1));
}

void Sprite::Draw(const GLuint VBO, const GLuint IBO, GLSLProgram *shader) const
{
	//copy vertices to GPU in case they have changed
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLvoid *vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(vBuffer, m_corners, sizeof(Vertex)*4);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBindTexture(GL_TEXTURE_2D, m_uiTexture);

	shader->setUniform("world", this->m_globalTransform);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT,GL_FALSE, sizeof(struct Vertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT,GL_FALSE, sizeof(struct Vertex), (void*)(sizeof(glm::vec4)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)(sizeof(glm::vec4)*2));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

AABB Sprite::getAABB() const
{
	AABB box;
	box.min.x = box.max.x = m_oCentrePos.x;
	box.min.y = box.max.y = m_oCentrePos.y;
	for(unsigned int i = 0; i < 4; ++i)
	{
		glm::vec4 temp = m_globalTransform * m_corners[i].position;
		if(temp.x < box.min.x)
			box.min.x = temp.x;
		if(temp.y < box.min.y)
			box.min.y = temp.y;
		if(temp.x > box.max.x)
			box.max.x = temp.x;
		if(temp.y > box.max.y)
			box.max.y = temp.y;
	}
	return box;
}

void Sprite::changeColour(const glm::vec4 a_oNewColour)
{
	for(unsigned int i = 0; i < 4; ++i)
	{
		m_corners[i].colour = a_oNewColour;
	}
}

void Sprite::setSpriteUVCoords(const float a_fUleft, const float a_fVbottom, const float a_fUright, const float a_fVtop)
{
	m_corners[0].texCoords.s = m_corners[1].texCoords.s = a_fUright;
	m_corners[2].texCoords.s = m_corners[3].texCoords.s = a_fUleft;
	m_corners[0].texCoords.t = m_corners[3].texCoords.t = a_fVbottom;
	m_corners[1].texCoords.t = m_corners[2].texCoords.t = a_fVtop;
}