#include "Engine.h"
#include "Log.h"
#include "GL/glew.h"

TakeOne::Engine::Engine(int pWidth, int pHeight, std::string pTitle) :
    mWindowTitle(pTitle), mShouldClose(false)
{
	//init glfw
	glfwSetErrorCallback(Engine::ErrorCallback);
	if (!glfwInit())
	{
		LOG_MSG("glfwInit Failed!");
	}

	//create window
    mWindow = glfwCreateWindow(pWidth, pHeight, mWindowTitle.c_str(), NULL, NULL);

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
    //VSync: 0->off, 1->on
    glfwSwapInterval(1);

    InitGlew();

    mInput.Init(mWindow);
}

TakeOne::Engine::~Engine()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

bool TakeOne::Engine::ShouldClose()
{
	//convert to bool before returning to avoid warning
    return glfwWindowShouldClose(mWindow) != 0 || glfwGetKey(mWindow, GLFW_KEY_ESCAPE ) == GLFW_PRESS || mShouldClose;
}

void TakeOne::Engine::SetShoudlClose(bool pShouldClose)
{
    mShouldClose = pShouldClose;
}

void TakeOne::Engine::SetUpdateCallback(UpdateCallback pCallback)
{
    mUpdateCallback = pCallback;
}

void TakeOne::Engine::SetDrawCallback(DrawCallback pCallback)
{
    mDrawCallback = pCallback;
}

void TakeOne::Engine::Run()
{
    double lastTime = glfwGetTime();
    while(!ShouldClose())
    {
        double now = glfwGetTime();
        double dt = now - lastTime;
        lastTime = now;

        mUpdateCallback(dt);
        mDrawCallback();

        //update engine
        Update(dt);
    }
}

TakeOne::Input& TakeOne::Engine::GetInput()
{
    return mInput;
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void TakeOne::Engine::Update(double pDt)
{
    //calculate fps
    static int updateRate = 4;  // 4 updates per sec.
    static int frameCount = 0;
    static double fps = 0.0;
    static double dtAcc = 0.0;

    frameCount++;
    dtAcc += pDt;
    if (dtAcc > 1.0/updateRate)
    {
        fps = frameCount / dtAcc ;
        frameCount = 0;
        dtAcc -= 1.0/updateRate;
    }

    glfwSetWindowTitle(mWindow, std::string(mWindowTitle +
                                            "  FPS: "+ std::to_string(fps) +
                                            "  DT: " + std::to_string(pDt)).c_str());

    //get the events, then swap buffers
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
}

void TakeOne::Engine::ErrorCallback(int pError, const char* pDescription)
{
	LOG_MSG("GLFW Error[%d]: %s", pError, pDescription);
}
