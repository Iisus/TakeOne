#include <Input.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

std::vector<TakeOne::Input::KeyboardCallback> TakeOne::Input::mKeyboardCallbacks = {};
std::vector<TakeOne::Input::MousePressCallback> TakeOne::Input::mMousePressCallbacks = {};
std::vector<TakeOne::Input::MousePosCallback> TakeOne::Input::mMousePosCallbacks = {};
std::vector<TakeOne::Input::MouseScrollCallback> TakeOne::Input::mMouseScrollCallbacks = {};

TakeOne::Input::Input()
{

}

TakeOne::Input::~Input()
{
    Cleanup();
}

void TakeOne::Input::Init(GLFWwindow* pWindow)
{
    mWindow = pWindow;

    glfwSetKeyCallback(mWindow, KeyboadCallbackGLFW);
    glfwSetMouseButtonCallback(mWindow, MousePressCallbackGLFW);
    glfwSetCursorPosCallback(mWindow, MousePosCallbackGLFW);
    glfwSetScrollCallback(mWindow, MouseScrollCallbackGLFW);
}

void TakeOne::Input::Cleanup()
{
    if(mWindow)
    {
        glfwSetKeyCallback(mWindow, nullptr);
        glfwSetMouseButtonCallback(mWindow, nullptr);
        glfwSetCursorPosCallback(mWindow, nullptr);
        glfwSetScrollCallback(mWindow, nullptr);

        mWindow = nullptr;
    }
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

int TakeOne::Input::RegisterKeyboardAction(KeyboardCallback aKeyboardCallback)
{
    mKeyboardCallbacks.push_back(aKeyboardCallback);
    return mKeyboardCallbacks.size() - 1;
}

int TakeOne::Input::RegisterMousePressAction(MousePressCallback aMousePressCallback)
{
    mMousePressCallbacks.push_back(aMousePressCallback);
    return mMousePressCallbacks.size() - 1;
}

int TakeOne::Input::RegisterMousePosAction(MousePosCallback aMousePosCallback)
{
    mMousePosCallbacks.push_back(aMousePosCallback);
    return mMousePosCallbacks.size() -1;
}

int TakeOne::Input::RegisterMouseScrollAction(MouseScrollCallback aMouseScrollCallback)
{
    mMouseScrollCallbacks.push_back(aMouseScrollCallback);
    return mMouseScrollCallbacks.size() - 1;
}

void TakeOne::Input::UnregisterKeyboardAction(int pHandle)
{
    if(pHandle < static_cast<int>(mKeyboardCallbacks.size()))
        mKeyboardCallbacks.erase(mKeyboardCallbacks.begin() + pHandle);
}

void TakeOne::Input::UnregisterMousePressAction(int pHandle)
{
    if(pHandle < static_cast<int>(mMousePressCallbacks.size()))
        mMousePressCallbacks.erase(mMousePressCallbacks.begin() + pHandle);
}
void TakeOne::Input::UnregisterMousePosAction(int pHandle)
{
    if(pHandle < static_cast<int>(mMousePosCallbacks.size()))
        mMousePosCallbacks.erase(mMousePosCallbacks.begin() + pHandle);
}
void TakeOne::Input::UnregisterMouseScrollAction(int pHandle)
{
    if(pHandle < static_cast<int>(mMouseScrollCallbacks.size()))
        mMouseScrollCallbacks.erase(mMouseScrollCallbacks.begin() + pHandle);
}

void TakeOne::Input::SetMousePosition(double pXPos, double pYPos)
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
