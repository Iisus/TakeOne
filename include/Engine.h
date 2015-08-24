#pragma once

#define GLFW_INCLUDE_NONE
#include "Input.h"
#include "State.h"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <memory>

namespace TakeOne
{
    class Engine
    {
    public:
        //public methods
        Engine(int pWidth, int pHeight, std::string pTitle);
        Engine(const Engine& Engine) = delete;
        Engine& operator=(const Engine& pEngine) = delete;
        Engine(Engine&& Engine) = delete;
        Engine& operator=(Engine&& pEngine) = delete;
        ~Engine();

        void Init(bool pVSync);
        void Cleanup();

        bool ShouldClose();
        void SetShoudlClose(bool pShouldClose = true);

        void Run();

        void PushState(State* pState);
        State* PopState();

        Input& GetInput();

    private:
        //private methods
        void InitGlew();
        static void ErrorCallback(int pError, const char* pDescription);

        std::vector<State*> mStates;

        Input mInput;

        //private members
        GLFWwindow* mWindow; //reference to window object; managed by glfw library
        std::string mWindowTitle;

        bool mShouldClose;

    };
}
