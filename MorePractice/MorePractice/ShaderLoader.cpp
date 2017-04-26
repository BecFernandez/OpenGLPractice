#include "ShaderLoader.h"

GLSLProgram::GLSLProgram()
{
	m_bLinked = false;
	m_iHandle = 0;
};

bool GLSLProgram::compileShaderFromFile(const char* filename, GLSLShaderType type)
{
	GLuint shader;
	switch(type)
	{
	case VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case GEOMETRY:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case TESS_CONTROL:
		shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case TESS_EVAL:
		shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	}
	if(shader == 0)
	{
		std::cerr << "Error creating shader" << std::endl;
		return false;
	}

	//load shader in from file
	FILE *input;
	fopen_s(&input, filename, "rb");
	if(input == NULL) 
	{
		std::cerr << "Error opening file " << filename << std::endl;
		return false;
	}
	if(fseek(input, 0, SEEK_END) == -1)
		return false;
	long size = ftell(input);
	if(size == -1)
		return false;
	if(fseek(input, 0, SEEK_SET) == -1)
		return false;
	char *content = (char*)malloc((size_t)size + 1);
	if(content == NULL)
		return false;

	fread(content, 1, (size_t)size, input);
	if(ferror(input))
	{
		free(content);
		std::cerr << "Error reading from file: " <<  filename<< std::endl;
		return false;
	}

	fclose(input);
	content[size] = '\0';

	//copy string to shader object
	const GLchar* codeArray[] = {content};

	glShaderSource(shader, 1, codeArray, NULL);

	//compile shader
	glCompileShader(shader);

	//check that it worked
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE)
	{
		std::cout << "Shader compilation failed" << std::endl;

		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

		if(logLen > 0)
		{
			char* log = (char*)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			std::cerr << log << std::endl;
			free(log);
		}
		return false;
	}

	//attach shader to program
	if(m_iHandle == 0)
	{
		m_iHandle = glCreateProgram();
		if(m_iHandle == 0)
		{
			std::cerr << "Error creating shader program" << std::endl;
			return false;
		}	
	}
	glAttachShader(m_iHandle, shader);

	return true;
}

bool GLSLProgram::compileShaderFromString(const std::string & source, GLSLShaderType type)
{
	return false;
}

bool GLSLProgram::link()
{
	glLinkProgram(m_iHandle);

	GLint status;
	glGetProgramiv(m_iHandle, GL_LINK_STATUS, &status);
	if(status == GL_FALSE)
	{
		std::cerr << "Failed to link shader program" << std::endl;
		GLint logLen;
		glGetProgramiv(m_iHandle, GL_INFO_LOG_LENGTH, &logLen);
		if(logLen > 0)
		{
			char*log = new char[logLen];
			GLsizei written;
			glGetProgramInfoLog(m_iHandle, logLen, &written, log);
			std::cerr << log << std::endl;
			delete [] log;
		}
		m_bLinked = false;
		return false;
	}
	m_bLinked = true;
	return true;
}

bool GLSLProgram::use() const
{
	if(m_iHandle)
	{
		glUseProgram(m_iHandle);
		return true;
	}
	return false;
}

int GLSLProgram::getHandle() const
{
	return m_iHandle;
}

bool GLSLProgram::isLinked() const
{
	return m_bLinked;
}

void GLSLProgram::bindAttribLocation(GLuint location, const char* name) const
{
	glBindAttribLocation(m_iHandle, location, name);
}

//void GLSLProgram::bindFragDataLocation(GLuint location, const char* name)
//{
//	
//}

void GLSLProgram::setUniform(const char* name, float x, float y, float z) const
{
	glUniform3f(getUniformLocation(name), x, y, z);
}

void GLSLProgram::setUniform(const char* name, const glm::mat4 & m) const
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

GLint GLSLProgram::getUniformBlockInfo(const char * blockName, const int numOfItems, const char ** blockItems, GLint *offsets, GLubyte *blockBuffer) const
{
	GLint blockSize;

	GLuint blockIndex = glGetUniformBlockIndex(m_iHandle, blockName);
	glGetActiveUniformBlockiv(m_iHandle, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
	blockBuffer = (GLubyte *)malloc(blockSize);
	//query for the offsets of each variable
	GLuint *indices = new GLuint[numOfItems];

	glGetUniformIndices(m_iHandle, numOfItems, blockItems, indices);
	
	if(offsets != NULL)
	{
		delete [] offsets;
	}
	offsets = new GLint[numOfItems];
	glGetActiveUniformsiv(m_iHandle, numOfItems, indices, GL_UNIFORM_OFFSET, offsets);
	delete [] indices;
	return blockSize;
}

/**************
  Private
*************/
int GLSLProgram::getUniformLocation(const char* name) const
{
	return glGetUniformLocation(m_iHandle, name);
}

bool GLSLProgram::fileExists(const std::string & filename)
{
	return false;
}