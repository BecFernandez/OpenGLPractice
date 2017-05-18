#include <GL\glew.h>
#include <GL\glfw3.h>
#include <iostream>
#include <gtc\matrix_transform.hpp>
#include "GameScreen.h"
#include <stack>
#include "InitResources.h"
#include "MainMenuScreen.h"

bool windowClosed = false;
bool fullscreen = false;

void error_callback(int error, const char* description)
{
	std::cout << error << " " << description << std::endl;
}

void APIENTRY openglCallbackFunction(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam) {

	std::cout << "---------------------opengl-callback-start------------" << std::endl;
	std::cout << "message: " << message << std::endl;
	std::cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	}
	std::cout << std::endl;

	std::cout << "id: " << id << std::endl;
	std::cout << "severity: ";
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	}
	std::cout << std::endl;
	std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}

bool init(GLFWwindow*& window)
{
	GLenum err = glfwInit();
	if(err != GLFW_TRUE)
	{
		std::cerr << "Error initialising glfw" << std::endl;
		return false;
	}

	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	window = glfwCreateWindow(800, 600, "Prac", NULL, NULL);
	
	
	if(!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	checkGLError("glfw init");

	glewExperimental = GL_TRUE;
	GLenum gerr = glewInit();
	if(GLEW_OK != gerr)
	{
		glfwTerminate();
		std::cerr << "Error initialising glew: " << glewGetErrorString(gerr) << std::endl;
		return false;
	}

	//if (glDebugMessageCallback) {
	//	std::cout << "Register OpenGL debug callback " << std::endl;
	//	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	//	//glDebugMessageCallback(openglCallbackFunction, nullptr);
	//	GLuint unusedIds = 0;
	//	glDebugMessageControl(GL_DONT_CARE,
	//		GL_DONT_CARE,
	//		GL_DONT_CARE,
	//		0,
	//		&unusedIds,
	//		true);
	//}
	//else
	//	std::cout << "glDebugMessageCallback not available" << std::endl;

	checkGLError("glew init");

	glEnable(GL_DEPTH_TEST); // Depth Testing
	checkGLError("depth test");
    glDepthFunc(GL_LEQUAL);
	checkGLError("depth func");
    glEnable(GL_CULL_FACE);
	checkGLError("disable cull face");
    glCullFace(GL_BACK);
	checkGLError("cull back");

	InitResources();
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

	glClearColor(1.0, 0.0, 0.0, 1.0);

	//set up audio engine
	SoundSystemClass sounds;

	Screen* currentScreen;

	MainMenuScreen *mms = new MainMenuScreen(&sounds);
	currentScreen = mms;

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

		
		
		//update
		Screen* next = currentScreen->Update(deltaTime);
		//if returned screen is null, pop current screen
		if(next != currentScreen)
		{
			delete currentScreen;
			currentScreen = next;
		}
		//else continue with current top of stack
		glfwSwapBuffers(window);
		
		glfwPollEvents();
		lastTime = currentTime;

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
