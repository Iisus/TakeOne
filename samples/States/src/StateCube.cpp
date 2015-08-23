#include "StateCube.h"
#include "StateSphere.h"
#include "DefaultRes.h"

StateCube::StateCube(Engine *pEngine)
    : State(pEngine)
{
    //setup camera
    mCamera.SetClearColor(glm::vec4(63.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f, 1.0));
    mCamera.SetPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100000.0f);
}

void StateCube::SetNextState(State* pNextState)
{
    mNextState = pNextState;
}

void StateCube::SetPrevState(State* pPrevState)
{
    mPrevState = pPrevState;
}

void StateCube::Enter()
{
    //callback for mouse wheel: change camera fov
    mMouseScroolCallbackHandle = mEngine->GetInput().RegisterMouseScrollAction(
    [this](double /*xoffset*/, double yoffset)
    {
        auto tempFov = mCamera.GetFOV() + (-1) * glm::radians(yoffset);
        if(tempFov > 0 && tempFov < glm::radians(120.0f))
            mCamera.SetPerspective(tempFov, mCamera.GetAspectRatio(), mCamera.GetNearPlane(), mCamera.GetFarPlane());
    });

    //callback for mouse position: rotate camera
    mMousePosCallbackHandle = mEngine->GetInput().RegisterMousePosAction(
    [this](double pXPos, double pYPos)
    {
        static float mouseSpeed = 0.001;

        static double oldX = pXPos, oldY = pYPos;

        static float horizontalAngle = 0;
        horizontalAngle -= mouseSpeed * float( pXPos - oldX);
        static float verticalAngle = 0;
        verticalAngle -= mouseSpeed * float( pYPos - oldY);

        mCamera.SetAngleAxis(horizontalAngle, glm::vec3(0, 1, 0));
        mCamera.Rotate(verticalAngle, glm::vec3(1,0,0));

        oldX = pXPos;
        oldY = pYPos;
    });

    //callback for keyboard
    mKeyboardCallbackHandle = mEngine->GetInput().RegisterKeyboardAction(
    [this](int pKey, int /*pScancode*/, int pAction, int /*pMods*/)
    {
        if(pAction == GLFW_RELEASE)
            mPressedKeys[pKey] = false;
        else if(pAction == GLFW_PRESS)
            mPressedKeys[pKey] = true;
    });

    mEngine->GetInput().SetCursorMode(GLFW_CURSOR_DISABLED);

    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    mProgram = std::shared_ptr<Program>(std::move(defaultRes.SimpleTextureProgram()));

    SetupBoxRenderer();

    mBox1Node.SetRenderObject(mBoxRenderer);
    mBox1Node.GetTransform().SetScale(glm::vec3(1.0f));
}

void StateCube::Exit()
{
    mEngine->GetInput().UnregisterMouseScrollAction(mMouseScroolCallbackHandle);
    mEngine->GetInput().UnregisterMousePosAction(mMousePosCallbackHandle);
    mEngine->GetInput().UnregisterKeyboardAction(mKeyboardCallbackHandle);
}

void StateCube::HandleEvents()
{

}

void StateCube::Update()
{
    //done here and not in HandleEvents because here is a fixed time step
    //and in UpdateInput, the camera position is modified
    UpdateInput();
}

void StateCube::Draw()
{
    mBoxRenderer->GetMaterial().SetShaderParam("u_Camera", mCamera.GetViewProjectionMatrix());
    mBox1Node.SendModelMatrix("u_ModelMatrix");

    mBoxRenderer->Render();
}

void StateCube::SetupBoxRenderer()
{
    mBoxRenderer = std::make_shared<BoxRenderObject>(mProgram);

    Texture diffuseTx(SampleUtil::RES_FOLDER + "textures/container2.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);

    mBoxRenderer->GetMaterial().SetTexture(std::move(diffuseTx));
}

void StateCube::UpdateInput()
{
    static int cursorMode = GLFW_CURSOR_DISABLED;
    static float speed = 0.0002;

    static glm::vec3 camPos(0.0f, 0.0f, 0.0f);

    //catch the release of M key
    static bool key_m_before = mPressedKeys[GLFW_KEY_M];
    if (!mPressedKeys[GLFW_KEY_M] && key_m_before){

        cursorMode = (cursorMode == GLFW_CURSOR_DISABLED)
                ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;

        mEngine->GetInput().SetCursorMode(cursorMode);
    }
    key_m_before = mPressedKeys[GLFW_KEY_M];

    if (mPressedKeys[GLFW_KEY_W]){
        camPos += mCamera.GetFrontDir() * speed;
    }

    if (mPressedKeys[GLFW_KEY_S]){
        camPos -= mCamera.GetFrontDir() * speed;
    }

    if (mPressedKeys[GLFW_KEY_D]){
        camPos += mCamera.GetRightDir() * speed;
    }

    if (mPressedKeys[GLFW_KEY_A]){
        camPos -= mCamera.GetRightDir() * speed;
    }

    if (mPressedKeys[GLFW_KEY_Q]){
        camPos -= mCamera.GetUpDir() * speed;
    }

    if (mPressedKeys[GLFW_KEY_E]){
        camPos += mCamera.GetUpDir() * speed;
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
