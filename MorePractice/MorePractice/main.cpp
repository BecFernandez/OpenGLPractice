#include <GL\glew.h>
#include <GL\glfw.h>
#include <iostream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "ShaderLoader.h"
#include "Player.h"
#include "Enemy.h"

using glm::vec3;
using glm::mat4;

bool windowClosed = false;
bool fullscreen = false;
GLSLProgram shaders;

static int GLFWCALL windowCloseListener()
{
	windowClosed = true;
	return 0;
}

bool init()
{
	GLenum err = glfwInit();
	if(!err)
	{
		std::cerr << "Error initialising glfw" << std::endl;
		return false;
	}

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE); //investigate resizing with glfw
	glfwOpenWindow(1024, 768, 
		8,8,8,8, //bits per colour channel
		24, //depth bits
		8, //stencil bits
		fullscreen? GLFW_FULLSCREEN:GLFW_WINDOW);
	glfwSetWindowTitle("Prac");
	glfwSwapInterval(1);
	glfwSetWindowCloseCallback(&windowCloseListener);

	GLenum gerr = glewInit();
	if(GLEW_OK != gerr)
	{
		glfwTerminate();
		std::cerr << "Error initialising glew: " << glewGetErrorString(gerr) << std::endl;
		return false;
	}
	return true;
}

void update(float dt)
{
	
}

void draw(float dt)
{
	
}

int main()
{
	if(!init())
	{
		system("pause");
		exit(0);
	}

	glClearColor(0.0, 0.0, 0.2, 1.0);

	//load shaders, compile and link	
	shaders.compileShaderFromFile("triangle.v.glsl", VERTEX);
	shaders.compileShaderFromFile("triangle.f.glsl", FRAGMENT);
	shaders.link();
	shaders.use();

	//create VBO and IBO for sprites - they are out here so all sprites can share buffers
	GLuint spriteVBO;
	glGenBuffers(1, &spriteVBO);
	glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
	//stream draw is to tell OpenGL that the data in this buffer will be modified every frame
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex)*4, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int spriteIndices[6] = {0, 1, 2, 0, 2, 3};
	GLuint spriteIBO;
	glGenBuffers(1, &spriteIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*6, &spriteIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//set up sprite
	//image credit to Itsomi on deviantart - http://www.deviantart.com/art/Viper-MkII-sprite-59124754
	Player fuzz(glm::vec3(1024/2, 768/2, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "ship.png");
	Enemy cylon(glm::vec3(100, 100, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "cylon.png");
	float angle = 0;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//create projection matrix
	glm::mat4 projectionMatrix = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f);

	while(glfwGetWindowParam(GLFW_OPENED) != 0 && !windowClosed)
	{
		//update
		fuzz.Update();
		cylon.Update(fuzz.getCentrePos());

		//draw
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaders.use();
		//set projection view matrix
		shaders.setUniform("projectionView", projectionMatrix);



		fuzz.Draw(spriteVBO, spriteIBO, &shaders);
		cylon.Draw(spriteVBO, spriteIBO, &shaders);

		glfwSwapBuffers();
	}

	glDeleteBuffers(1, &spriteIBO);
	glDeleteBuffers(1, &spriteVBO);
	return 0;
}
