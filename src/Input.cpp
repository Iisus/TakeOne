#include <Input.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

std::vector<TakeOne::Input::KeyboardCallback> TakeOne::Input::mKeyboardCallbacks = {};
std::vector<TakeOne::Input::MousePressCallback> TakeOne::Input::mMousePressCallbacks = {};
std::vector<TakeOne::Input::MousePosCallback> TakeOne::Input::mMousePosCallbacks = {};
std::vector<TakeOne::Input::MouseScrollCallback> TakeOne::Input::mMouseScrollCallbacks = {};

void TakeOne::Input::Init(GLFWwindow* pWindow)
{
    mWindow = pWindow;

    glfwSetKeyCallback(mWindow, KeyboadCallbackGLFW);
    glfwSetMouseButtonCallback(mWindow, MousePressCallbackGLFW);
    glfwSetCursorPosCallback(mWindow, MousePosCallbackGLFW);
    glfwSetScrollCallback(mWindow, MouseScrollCallbackGLFW);
}

int TakeOne::Input::GetKeyState(int pKey) const
{
    return glfwGetKey(mWindow, pKey);
}

int TakeOne::Input::GetMouseBtnState(int pBtn) const
{
    return glfwGetMouseButton(mWindow, pBtn);
}

glm::vec2 TakeOne::Input::GetCursorPos() const
{
    double x, y;
    glfwGetCursorPos(mWindow, &x, &y);

    return glm::vec2(x, y);
}

void TakeOne::Input::KeyboardAction(KeyboardCallback aKeyboardCallback)
{
    mKeyboardCallbacks.push_back(aKeyboardCallback);
}

void TakeOne::Input::MousePressAction(MousePressCallback aMousePressCallback)
{
    mMousePressCallbacks.push_back(aMousePressCallback);
}

void TakeOne::Input::MousePosAction(MousePosCallback aMousePosCallback)
{
    mMousePosCallbacks.push_back(aMousePosCallback);
}

void TakeOne::Input::MouseScrollAction(MouseScrollCallback aMouseScrollCallback)
{
    mMouseScrollCallbacks.push_back(aMouseScrollCallback);
}

void TakeOne::Input::MouseSetPosition(double pXPos, double pYPos)
{
    glfwSetCursorPos(mWindow, pXPos, pYPos);
}

void TakeOne::Input::SetCursorMode(int pMode)
{
    glfwSetInputMode(mWindow, GLFW_CURSOR, pMode);
}

void TakeOne::Input::KeyboadCallbackGLFW(GLFWwindow* /*pWindow*/, int pKey, int pScancode, int pAction, int pMods)
{
    for(const auto& f : mKeyboardCallbacks)
        f(pKey, pScancode, pAction, pMods);
}

void TakeOne::Input::MousePressCallbackGLFW(GLFWwindow* /*pWindow*/, int pButton, int pAction, int pMods)
{
    for(const auto& f : mMousePressCallbacks)
        f(pButton, pAction, pMods);
}

void TakeOne::Input::MousePosCallbackGLFW(GLFWwindow* /*pWindow*/, double pXPos, double pYPos)
{
    for(const auto& f : mMousePosCallbacks)
        f(pXPos, pYPos);
}

void TakeOne::Input::MouseScrollCallbackGLFW(GLFWwindow* /*pWindow*/, double pXOffset, double pYOffset)
{
    for(const auto& f : mMouseScrollCallbacks)
        f(pXOffset, pYOffset);
}
