#include <GL\glew.h>
#include <GL\glfw3.h>
#include <iostream>
#include <gtc\matrix_transform.hpp>
#include "GameScreen.h"
#include <stack>
#include "MainMenuScreen.h"
#include "Text.h"

bool windowClosed = false;
bool fullscreen = false;

bool init(GLFWwindow*& window)
{
	GLenum err = glfwInit();
	if(!err)
	{
		std::cerr << "Error initialising glfw" << std::endl;
		return false;
	}
	window = glfwCreateWindow(800, 600, "Prac", NULL, NULL);
	
	if(!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	GLenum gerr = glewInit();
	if(GLEW_OK != gerr)
	{
		glfwTerminate();
		std::cerr << "Error initialising glew: " << glewGetErrorString(gerr) << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
	return true;
}

int main()
{
	GLFWwindow* window = nullptr;
	if(!init(window))
	{
		system("pause");
		exit(0);
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);

	//set up audio engine
	SoundSystemClass sounds;

	GLSLProgram shaders;
	//load shaders, compile and link	
	shaders.compileShaderFromFile("triangle.v.glsl", VERTEX);
	shaders.compileShaderFromFile("triangle.f.glsl", FRAGMENT);
	shaders.link();
	shaders.use();

	Screen* currentScreen;

	MainMenuScreen *mms = new MainMenuScreen(&sounds, &shaders);
	currentScreen = mms;
	
	//Text t(glm::vec3(0, 0, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 40, 40, "arial_0.png", "arial.fnt");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//create projection matrix
	glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	double lastTime = glfwGetTime(), currentTime;

	while(!glfwWindowShouldClose(window) && currentScreen != nullptr)
	{
		//calculate delta time
		currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		//draw
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		currentScreen->Draw();

		glfwSwapBuffers(window);
		
		//update
		Screen* next = currentScreen->Update(deltaTime);
		//if returned screen is null, pop current screen
		if(next != currentScreen)
		{
			delete currentScreen;
			currentScreen = next;
		}
		//else continue with current top of stack

		
		glfwPollEvents();
		lastTime = currentTime;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
