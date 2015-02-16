#include "Sprite.h"
#include <FreeImage.h>
#include <iostream>
#include <gtc\matrix_transform.hpp>

unsigned int LoadTexture(const char * Texture, unsigned int format, unsigned int* width, unsigned int* height, unsigned int *bpp)
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

Sprite::Sprite(glm::vec3 a_position,
		glm::vec4 a_colour,
		unsigned int a_uiWidth, unsigned int a_uiHeight, const char* a_szTexName) 
		: m_oCentrePos(a_position), m_uiWidth(a_uiWidth), m_uiHeight(a_uiHeight), m_fRotationAngle(0)
{
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

glm::vec3 Sprite::getCentrePos()
{
	return m_oCentrePos;
}

float Sprite::getRotationAngle()
{
	return m_fRotationAngle;
}

void Sprite::Update(double a_dDeltaTime)
{
	//so in here I really just need to modify the world matrix
	m_globalTransform = glm::translate(glm::mat4(1), glm::vec3(m_oCentrePos.x, m_oCentrePos.y, m_oCentrePos.z)) *
		glm::rotate(glm::mat4(1), m_fRotationAngle, glm::vec3(0, 0, 1));
}

void Sprite::Draw(GLuint VBO, GLuint IBO, GLSLProgram *shader)
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