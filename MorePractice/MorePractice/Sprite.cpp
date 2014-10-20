#include "Sprite.h"
#include <FreeImage.h>
#include <iostream>

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

Sprite::Sprite(float x, float y, float z, float r, float g, float b, unsigned int w, unsigned int h, const char * texName)
{
	if(texName != NULL)
		texture = LoadTexture(texName, GL_RGBA, NULL, NULL, NULL);  
	this->centrex = x;
	this->centrey = y;
	this->centrez = z;

	this->width= w;
	this->height = h;

	for(int i = 0; i < 4; i++)
	{
		corners[i].posz = z;
		corners[i].r = r;
		corners[i].g = g;
		corners[i].b = b;
		corners[i].a = 1.0f;
		if(i/2)
		{
			corners[i].posx = centrex - width*0.5;
			corners[i].u = 0;
		}
		else
		{
			corners[i].posx = centrex + width*0.5;
			corners[i].u = 1;
		}
		if(i%3)
		{
			corners[i].posy = centrey + height*0.5;
			corners[i].v = 1;
		}
		else
		{
			corners[i].posy = centrey - height*0.5;
			corners[i].v = 0;
		}
	}
}

void Sprite::Draw(GLuint VBO, GLuint IBO, GLSLProgram *shader)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLvoid *vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(vBuffer, corners, sizeof(Vertex)*4);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(struct Vertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT,GL_FALSE, sizeof(struct Vertex), (void*)(sizeof(float)*3));


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);


	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}