#include "Engine.h"
#include "Log.h"

TakeOne::Engine::Engine(int pWidth, int pHeight, std::string pTitle)
{
	//init glfw
	glfwSetErrorCallback(Engine::ErrorCallback);
	if (!glfwInit())
	{
		LOG_MSG("glfwInit Failed!");
	}

	//create window
	mWindow = glfwCreateWindow(pWidth, pHeight, pTitle.c_str(), NULL, NULL);

	if (!mWindow)
	{
		LOG_MSG("glfwCreateWindow Failed!");
	}

	//use the context created
	glfwMakeContextCurrent(mWindow);	
}

TakeOne::Engine::~Engine()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void TakeOne::Engine::Update()
{
	//get the events, then swap buffers
	glfwPollEvents();
	glfwSwapBuffers(mWindow);
}

bool TakeOne::Engine::ShouldClose()
{
	//convert to bool before returning to avoid warning
	return !!glfwWindowShouldClose(mWindow);
}

void TakeOne::Engine::ErrorCallback(int pError, const char* pDescription)
{
	LOG_MSG("GLFW Error[%d]: %s", pError, pDescription);
}