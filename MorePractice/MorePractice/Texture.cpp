#include "Texture.h"
#include <FreeImage.h>
#include <GL\glew.h>
#include <GL\glfw3.h>
#include <iostream>

unsigned int LoadTexture2(const char * Texture, const unsigned int format, unsigned int* width, unsigned int* height, unsigned int *bpp)
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

Texture::Texture(const char* a_szPath) : m_szPath(a_szPath)
{
	m_uiTexHandle = LoadTexture2(m_szPath, GL_RGBA, &m_uiWidth, &m_uiHeight, &m_uiBPP);
}

Texture::~Texture()
{
	//better unload these textures somehow. How is FreeImage allocating them???
}
