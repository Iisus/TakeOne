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
        using UpdateCallback = void(*)(double);
        using DrawCallback = void(*)();

        //public methods
        Engine(int pWidth, int pHeight, std::string pTitle);
        Engine(const Engine& Engine) = delete;
        Engine& operator=(const Engine& pEngine) = delete;
        ~Engine();

        bool ShouldClose();
        void SetShoudlClose(bool pShouldClose = true);

        void SetUpdateCallback(UpdateCallback pCallback);
        void SetDrawCallback(DrawCallback pCallback);
        void Run();

        Input& GetInput();

    private:
        //private methods
        void InitGlew();
        void Update(double pDt);
        static void ErrorCallback(int pError, const char* pDescription);

        UpdateCallback mUpdateCallback;
        DrawCallback mDrawCallback;
        Input mInput;

        //private members
        GLFWwindow* mWindow; //reference to window object; managed by glfw library
        std::string mWindowTitle;

        bool mShouldClose;

    };
}
