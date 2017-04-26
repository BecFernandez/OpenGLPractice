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
	int m_iHandle;
	bool m_bLinked;
	int getUniformLocation(const char* name) const;
	bool fileExists(const std::string & filename);

public:
	GLSLProgram();
	bool compileShaderFromFile(const char* filename, GLSLShaderType type);
	bool compileShaderFromString(const std::string & source, GLSLShaderType type);
	bool link();
	bool use() const;
	int getHandle() const;
	bool isLinked() const;
	void bindAttribLocation(GLuint location, const char* name) const;
	//void bindFragDataLocation(GLuint location, const char* name);
	void setUniform(const char* name, float x, float y, float z) const;
	void setUniform(const char* name, const glm::mat4 &m) const;
	/*void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z);
	*/
	GLint getUniformBlockInfo(const char * blockName, const int numOfItems, const char ** blockItems, GLint *offsets, GLubyte *blockBuffer) const;

};

#endif