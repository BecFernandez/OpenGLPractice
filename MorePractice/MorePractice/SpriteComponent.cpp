#include "SpriteComponent.h"
#include <FreeImage.h>
#include <gtc\matrix_transform.hpp>

unsigned int LoadTexture(const char * Texture, const unsigned int format, unsigned int* width, unsigned int* height, unsigned int *bpp)
{
	FIBITMAP* bitmap = NULL;

	//check the file format signature, deduce its format and load it
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(Texture, 0);

	if (fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif))
	{
		bitmap = FreeImage_Load(fif, Texture);
	}

	if (bitmap == NULL)
	{
		std::cerr << "Error: Failed to load image " << Texture << std::endl;
		return 0;
	}

	if (width != NULL)
		*width = FreeImage_GetWidth(bitmap);
	if (height != NULL)
		*height = FreeImage_GetHeight(bitmap);

	//force image to RGBA - might change this
	unsigned int BitsPerPixel = FreeImage_GetBPP(bitmap);
	if (bpp != NULL)
		*bpp = BitsPerPixel / 8;

	FREE_IMAGE_COLOR_TYPE fiColourType = FreeImage_GetColorType(bitmap);
	if (fiColourType != FIC_RGBALPHA)
	{
		FIBITMAP* ndib = FreeImage_ConvertTo32Bits(bitmap);
		FreeImage_Unload(bitmap);
		bitmap = ndib;
		BitsPerPixel = FreeImage_GetBPP(bitmap);
		fiColourType = FreeImage_GetColorType(bitmap);
	}

	BYTE *data = FreeImage_GetBits(bitmap);

	FREE_IMAGE_TYPE fit = FreeImage_GetImageType(bitmap);
	GLenum eType = (fit == FIT_RGBF || fit == FIT_FLOAT) ? GL_FLOAT : GL_UNSIGNED_BYTE;

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

SpriteComponent::SpriteComponent(const glm::vec4 a_colour,
	const glm::vec2 a_dimensions, const char* a_szTexName,
	GLuint a_uiVBO, GLuint a_uiIBO, GLSLProgram* a_pShader) :
	m_dimensions(a_dimensions), m_uiVBO(a_uiVBO), m_uiIBO(a_uiIBO), m_pShader(a_pShader)
{
	//load texture - at run time? Sounds like a bad idea - why don't I load all the textures when the game starts
	//and here I just link to it?
	//for now let's just get the project working again and then we can refactor

	//also got to be a better way of setting width and height? Make my own container maybe?
	//Just go back to storing separate unsigned ints instead?
	unsigned int width = (unsigned int)a_dimensions.x;
	unsigned int height = (unsigned int)a_dimensions.y;
	if (a_szTexName != nullptr)
		m_uiTexture = LoadTexture(a_szTexName, GL_RGBA, &width, &height, NULL);
	else
		m_uiTexture = 0;

	m_dimensions.x = (float)width;
	m_dimensions.y = (float)height;

	for (int i = 0; i < 4; i++)
	{
		m_corners[i].position.z = 0;
		m_corners[i].position.w = 1;
		m_corners[i].colour = a_colour;

		if (i / 2)
		{
			m_corners[i].position.x = m_dimensions.x *0.5f * (float)-1;
			m_corners[i].texCoords.s = 0;
		}
		else
		{
			m_corners[i].position.x = m_dimensions.x*0.5f;
			m_corners[i].texCoords.s = 1;
		}
		if (i % 3)
		{
			m_corners[i].position.y = m_dimensions.y*0.5f;
			m_corners[i].texCoords.t = 1;
		}
		else
		{
			m_corners[i].position.y = m_dimensions.y*0.5f * (float)-1;
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

void SpriteComponent::Update(glm::vec3 a_position, float a_fRotationAngle, float a_fScale)
{
	m_globalTransform = glm::translate(glm::mat4(1), glm::vec3(a_position.x, a_position.y, a_position.z)) *
		glm::rotate(glm::mat4(1), a_fRotationAngle, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(a_fScale, a_fScale, 1));
}

void SpriteComponent::Draw() const
{
	//copy vertices to GPU in case they have changed
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	GLvoid *vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(vBuffer, m_corners, sizeof(Vertex) * 4);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);

	glBindTexture(GL_TEXTURE_2D, m_uiTexture);

	m_pShader->setUniform("world", this->m_globalTransform);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)(sizeof(glm::vec4)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)(sizeof(glm::vec4) * 2));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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