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
}

TakeOne::Engine::~Engine()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void TakeOne::Engine::Init(bool pVSync)
{
    //VSync: 0->off, 1->on
    glfwSwapInterval(pVSync);

    InitGlew();

    mInput.Init(mWindow);
}

void TakeOne::Engine::Cleanup()
{
    for (auto state = mStates.rbegin(); state != mStates.rend(); ++state)
    {
        (*state)->Exit();
    }

    mInput.Cleanup();
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

void TakeOne::Engine::Run()
{
    const int TICKS_PER_SECOND = 60;
    const double SKIP_TICKS = 1.0f / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 10;

    double nextUpdate = glfwGetTime();
    int loops;

    while(!ShouldClose())
    {
        ShowFPS();

        if(mStates.empty())
            break;

        State* currState = mStates.back();

        loops = 0;
        while(glfwGetTime() > nextUpdate && loops < MAX_FRAMESKIP)
        {
            glfwPollEvents();

            currState->HandleEvents();

            currState->Update();

            nextUpdate += SKIP_TICKS;
            loops++;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        currState->Draw();

        glfwSwapBuffers(mWindow);
    }
}

void TakeOne::Engine::PushState(State* pState)
{
    if(!mStates.empty())
        mStates.back()->Exit();

    mStates.push_back(pState);

    mStates.back()->Enter();
}

TakeOne::State* TakeOne::Engine::PopState()
{
    State* ret = nullptr;

    if(!mStates.empty())
    {
        mStates.back()->Exit();
        ret = mStates.back();

        mStates.pop_back();

        if(!mStates.empty())
            mStates.back()->Enter();
    }

    return ret;
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

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_ALPHA_TEST);
//    glAlphaFunc(GL_GREATER, 0.5f);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void TakeOne::Engine::ShowFPS()
{
    double currentTime = glfwGetTime ();
    static int nbFrames = 0;
    static double lastTime = 0;

    nbFrames++;

    if (currentTime - lastTime >= 0.5)
    {
      glfwSetWindowTitle(mWindow, std::string(mWindowTitle +
                         " [FPS: " + std::to_string((float)nbFrames / (currentTime - lastTime)) +
                         "] [DT: " + std::to_string((currentTime - lastTime) / (float)nbFrames) + "]").c_str());

      nbFrames = 0;
      lastTime = currentTime;
    }
}

void TakeOne::Engine::ErrorCallback(int pError, const char* pDescription)
{
	LOG_MSG("GLFW Error[%d]: %s", pError, pDescription);
}
