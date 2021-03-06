#pragma once

#include <vector>
#include <functional>
#include "glm/glm.hpp"

class GLFWwindow;

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

        //Pool
        int GetKeyState(int pKey) const;
        int GetMouseBtnState(int pBtn) const;
        glm::vec2 GetCursorPos() const;

        //Event based
        int RegisterKeyboardAction(KeyboardCallback aKeyboardCallback);
        int RegisterMousePressAction(MousePressCallback aMousePressCallback);
        int RegisterMousePosAction(MousePosCallback aMousePosCallback);
        int RegisterMouseScrollAction(MouseScrollCallback aMouseScrollCallback);

        void UnregisterKeyboardAction(int pHandle);
        void UnregisterMousePressAction(int pHandle);
        void UnregisterMousePosAction(int pHandle);
        void UnregisterMouseScrollAction(int pHandle);

        void SetMousePosition(double pXPos, double pYPos);
        void SetCursorMode(int pMode);

    protected:
        friend class Engine;

        Input();
        ~Input();
        void Init(GLFWwindow* pWindow);
        void Cleanup();

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
