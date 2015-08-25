#include "StateSample.h"
#include "DefaultRes.h"
#include <iostream>

StateSample::StateSample(Engine *pEngine)
    : State(pEngine), mCameraMoveSpeed(1), mCameraRotateSpeed(0.001)
{
    //setup camera
    mCamera.SetClearColor(glm::vec4(63.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f, 1.0));
    mCamera.SetPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100000.0f);
    mCamera.SetAngleAxis(vec4(0, 0, 1, 0));
}

void StateSample::SetNextState(State* pNextState)
{
    mNextState = pNextState;
}

void StateSample::SetPrevState(State* pPrevState)
{
    mPrevState = pPrevState;
}

void StateSample::Enter()
{
    //callback for mouse wheel: change camera fov
    mMouseScroolCallbackHandle = mEngine->GetInput().RegisterMouseScrollAction(
    [this](double pXOffset, double pYOffset)
    {
        auto tempFov = mCamera.GetFOV() + (-1) * glm::radians(pYOffset);
        if(tempFov > 0 && tempFov < glm::radians(120.0f))
            mCamera.SetPerspective(tempFov, mCamera.GetAspectRatio(), mCamera.GetNearPlane(), mCamera.GetFarPlane());

        //callback
        this->MouseScrool(pXOffset, pYOffset);
    });

    mMouseBtnCallbackHandle = mEngine->GetInput().RegisterMousePressAction(
    [this](int pButton, int pAction, int pMods)
    {
        //callback
        this->MouseBtnPress(pButton, pAction, pMods);
    });

    //callback for mouse position: rotate camera
    mEngine->GetInput().SetMousePosition(0,0);
    mMousePosCallbackHandle = mEngine->GetInput().RegisterMousePosAction(
    [this](double pXPos, double pYPos)
    {
        mCamera.SetAngleAxis(-mCameraRotateSpeed*pXPos, vec3(0, 1, 0));
        mCamera.Rotate(-mCameraRotateSpeed*pYPos, vec3(1, 0, 0));

        //callback
        this->MousePos(pXPos, pYPos);
    });

    //callback for keyboard
    mKeyboardCallbackHandle = mEngine->GetInput().RegisterKeyboardAction(
    [this](int pKey, int pScancode, int pAction, int pMods)
    {
        if(pAction == GLFW_RELEASE)
            mPressedKeys[pKey] = false;
        else if(pAction == GLFW_PRESS)
            mPressedKeys[pKey] = true;

        //callback
        this->Keyboard(pKey, pScancode, pAction, pMods);
    });

    mEngine->GetInput().SetCursorMode(GLFW_CURSOR_DISABLED);
}

void StateSample::Exit()
{
    mEngine->GetInput().UnregisterMouseScrollAction(mMouseScroolCallbackHandle);
    mEngine->GetInput().UnregisterMousePressAction(mMouseBtnCallbackHandle);
    mEngine->GetInput().UnregisterMousePosAction(mMousePosCallbackHandle);
    mEngine->GetInput().UnregisterKeyboardAction(mKeyboardCallbackHandle);

    mPressedKeys = {};
}

void StateSample::HandleEvents()
{
    static int cursorMode = GLFW_CURSOR_DISABLED;

    glm::vec3 camPos = mCamera.GetTransform().GetPosition();

    //catch the release of M key
    static bool key_m_before = mPressedKeys[GLFW_KEY_M];
    if (!mPressedKeys[GLFW_KEY_M] && key_m_before){

        cursorMode = (cursorMode == GLFW_CURSOR_DISABLED)
                ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;

        mEngine->GetInput().SetCursorMode(cursorMode);
    }
    key_m_before = mPressedKeys[GLFW_KEY_M];

    if (mPressedKeys[GLFW_KEY_W]){
        camPos += mCamera.GetFrontDir() * mCameraMoveSpeed;
    }

    if (mPressedKeys[GLFW_KEY_S]){
        camPos -= mCamera.GetFrontDir() * mCameraMoveSpeed;
    }

    if (mPressedKeys[GLFW_KEY_D]){
        camPos += mCamera.GetRightDir() * mCameraMoveSpeed;
    }

    if (mPressedKeys[GLFW_KEY_A]){
        camPos -= mCamera.GetRightDir() * mCameraMoveSpeed;
    }

    if (mPressedKeys[GLFW_KEY_Q]){
        camPos -= mCamera.GetUpDir() * mCameraMoveSpeed;
    }

    if (mPressedKeys[GLFW_KEY_E]){
        camPos += mCamera.GetUpDir() * mCameraMoveSpeed;
    }

    if (mPressedKeys[GLFW_KEY_R]){
        mProgram->Reload();
    }

    //catch the release of page up key
    static bool key_pu_before = mPressedKeys[GLFW_KEY_PAGE_UP];
    if (!mPressedKeys[GLFW_KEY_PAGE_UP] && key_pu_before){
        mEngine->PopState();
        mEngine->PushState(mNextState);
    }
    key_pu_before = mPressedKeys[GLFW_KEY_PAGE_UP];

    //catch the release of page down key
    static bool key_pd_before = mPressedKeys[GLFW_KEY_PAGE_DOWN];
    if (!mPressedKeys[GLFW_KEY_PAGE_DOWN] && key_pd_before){
        mEngine->PopState();
        mEngine->PushState(mPrevState);
    }
    key_pd_before = mPressedKeys[GLFW_KEY_PAGE_DOWN];

    mCamera.GetTransform().SetPosition(camPos);
}

void StateSample::Update()
{

}

void StateSample::Draw()
{
    for(const auto& objects: mObjects)
        for(const auto& node : objects.second)
        {
            node->GetRenderObject()->GetMaterial().SetShaderParam("u_Camera", mCamera.GetViewProjectionMatrix());
            node->SendModelMatrix("u_ModelMatrix");

            node->GetRenderObject()->Render();
        }
}

void StateSample::LoadObject(const string& pObject)
{
    string scenePath = SampleUtil::RES_FOLDER + "objects/" + pObject + "/";
    ifstream sceneFile(scenePath + "/scene.txt");

    string objectName;
    while(std::getline(sceneFile, objectName))
    {
        AddObject(pObject, make_unique<RenderNode>(make_shared<RenderObject>(mProgram, scenePath, objectName)));
    }
}

void StateSample::AddObject(const string& pObjectName, unique_ptr<RenderNode> pNode)
{
    mObjects[pObjectName].push_back(std::move(pNode));
}
