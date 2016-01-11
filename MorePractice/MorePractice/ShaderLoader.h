#ifndef __SHADERLOADER_H__
#define __SHADERLOADER_H__

#include <GL\glew.h>
#include <GL\glfw3.h>
#include <string>
#include <glm.hpp>
#include <iostream>

enum GLSLShaderType
{
	VERTEX,
	FRAGMENT,
	GEOMETRY,
	TESS_CONTROL,
	TESS_EVAL
};

class GLSLProgram
{
private:
	int handle;
	bool linked;
	std::string logString;
	int getUniformLocation(const char* name);
	bool fileExists(const std::string & filename);

public:
	GLSLProgram();
	bool compileShaderFromFile(const char* filename, GLSLShaderType type);
	bool compileShaderFromString(const std::string & source, GLSLShaderType type);
	bool link();
	bool use();
	std::string log();
	int getHandle();
	bool isLinked();
	void bindAttribLocation(GLuint location, const char* name);
	void bindFragDataLocation(GLuint location, const char* name);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const glm::mat4 &m);
	/*void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	*/
	GLint getUniformBlockInfo(const char * blockName, const int numOfItems, const char ** blockItems, GLint *offsets, GLubyte *blockBuffer);

};

#endif