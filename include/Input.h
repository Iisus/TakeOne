#pragma once

#include <vector>
#include <functional>

class GLFWwindow;
class Engine;

namespace TakeOne
{
    class Input
    {
    private:
        using KeyboardCallback = std::function<void(int, int, int, int)>;
        using MousePressCallback = std::function<void(int, int, int)>;
        using MousePosCallback = std::function<void(double, double)>;
        using MouseScrollCallback = std::function<void(double, double)>;

    public:

        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;
        Input(Input&&) = delete;
        Input& operator=(Input&&) = delete;

        void KeyboardAction(KeyboardCallback aKeyboardCallback);
        void MousePressAction(MousePressCallback aMousePressCallback);
        void MousePosAction(MousePosCallback aMousePosCallback);
        void MouseScrollAction(MouseScrollCallback aMouseScrollCallback);

        void MouseSetPosition(double pXPos, double pYPos);
        void SetCursorMode(int pMode);

    protected:
        friend class Engine;

        Input(){}
        void Init(GLFWwindow* pWindow);

        GLFWwindow* mWindow;

    private:

        static void KeyboadCallbackGLFW(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods);
        static void MousePressCallbackGLFW(GLFWwindow* pWindow, int pButton, int pAction, int pMods);
        static void MousePosCallbackGLFW(GLFWwindow* pWindow, double pXPos, double pYPos);
        static void MouseScrollCallbackGLFW(GLFWwindow* pWindow, double pXOffset, double pYOffset);

        static std::vector<KeyboardCallback> mKeyboardCallbacks;
        static std::vector<MousePressCallback> mMousePressCallbacks;
        static std::vector<MousePosCallback> mMousePosCallbacks;
        static std::vector<MouseScrollCallback> mMouseScrollCallbacks;
    };
}
