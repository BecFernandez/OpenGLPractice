#include <GL\glew.h>
#include <GL\glfw3.h>
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



void update(float dt)
{
	
}

void draw(float dt)
{
	
}



int main()
{
	GLFWwindow* window = nullptr;
	if(!init(window))
	{
		system("pause");
		exit(0);
	}

	glClearColor(0.1, 0.0, 0.2, 0.0);

	SoundSystemClass sounds;
	


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
	
	std::vector<Bullet> bullets;

	//set up sprite
	//image credit to Itsomi on deviantart - http://www.deviantart.com/art/Viper-MkII-sprite-59124754
	Player fuzz(glm::vec3(800/2, 600/2, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "ship.png", &bullets, sounds);
	Enemy **cylons = new Enemy*[3];
	for(int i = 0; i < 3; i++)
	{
		cylons[i] = new Enemy(glm::vec3(rand()%800, rand()%600, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 51, 86, "cylon.png", &bullets, sounds);
	}
	float angle = 0;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//create projection matrix
	glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	double lastTime = glfwGetTime(), currentTime;

	while(!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		//update
		fuzz.Update(deltaTime, sounds);
		for(int i = 0; i < 3; i++)
			cylons[i]->Update(fuzz.getCentrePos(), deltaTime, sounds);

		//collisions - player & bullets
		for(unsigned int i = 0; i < bullets.size(); ++i)
		{
			if(AABBvsAABB(bullets[i].getAABB(), fuzz.getAABB()))
			{
				fuzz.changeColour(glm::vec4(1, 0, 0, 1));
			}
			//collisions bullets and cylons
			for(unsigned int j = 0; j < 3; ++j)
			{
				if(AABBvsAABB(bullets[i].getAABB(), cylons[j]->getAABB()))
				{
					cylons[j]->changeColour(glm::vec4(0, 1, 0, 1));
				}
			}
		}
		

		////collisions player and cylons
		//for(unsigned int i = 0; i < 3; ++i)
		//{
		//	if(AABBvsAABB(cylons[i]->getAABB(), fuzz.getAABB()))
		//	{
		//		cylons[i]->changeColour(glm::vec4(0, 1, 0, 1));
		//		fuzz.changeColour(glm::vec4(1, 0, 0, 1));
		//	}
		//}

		//draw
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaders.use();
		//set projection view matrix
		shaders.setUniform("projectionView", projectionMatrix);

		fuzz.Draw(spriteVBO, spriteIBO, &shaders);
		for(int i = 0; i < 3; i++)
			cylons[i]->Draw(spriteVBO, spriteIBO, &shaders);

		glfwSwapBuffers(window);
		glfwPollEvents();
		lastTime = currentTime;
	}

	//glDeleteBuffers(1, &spriteIBO);
	//glDeleteBuffers(1, &spriteVBO);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
