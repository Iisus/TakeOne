#include "Engine.h"
#include "Log.h"
#include "GL/glew.h"

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef ENABLE_DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

    if (!mWindow)
	{
		LOG_MSG("glfwCreateWindow Failed!");
	}

	//use the context created
	glfwMakeContextCurrent(mWindow);

    InitGlew();
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

void  TakeOne::Engine::InitGlew()
{
    glewExperimental=GL_TRUE;
    GLenum err = glewInit();

    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        LOG_MSG("Error: %s\n", glewGetErrorString(err));
    }

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_CLAMP);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void TakeOne::Engine::ErrorCallback(int pError, const char* pDescription)
{
	LOG_MSG("GLFW Error[%d]: %s", pError, pDescription);
}