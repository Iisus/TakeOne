#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

namespace TakeOne
{
    class Engine
    {
    public:
        //public methods
        Engine(int pWidth, int pHeight, std::string pTitle);
        Engine(const Engine& Engine) = delete;
        Engine& operator=(const Engine& pEngine) = delete;
        ~Engine();

        void Update();
        bool ShouldClose();

        //TODO: Remove this:
        GLFWwindow* GetWindow() { return mWindow; }

    private:
        //private methods
        void InitGlew();
        static void ErrorCallback(int pError, const char* pDescription);

        //private members
        GLFWwindow* mWindow; //reference to window object; managed by glfw library
    };
}
