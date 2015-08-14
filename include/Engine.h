#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <Input.h>

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

        Input& GetInput();

    private:
        //private methods
        void InitGlew();
        static void ErrorCallback(int pError, const char* pDescription);

        Input mInput;

        //private members
        GLFWwindow* mWindow; //reference to window object; managed by glfw library
    };
}
