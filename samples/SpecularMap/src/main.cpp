#include "SampleUtil.h"

#include "CameraNode.h"
#include "Primitives.h"
#include "RenderNode.h"

//-------------------------
//function prototypes
void Init(Engine&);
void Update(double);
void Draw();

void SetupBoxRenderer();
void SetupCamera(Engine&);

void UpdateKeyInput(Engine& pEngine, double pDt);
//-------------------------

//-------------------------
//Globals
CameraNode gCamera(TakeOne::CameraType::PERSPECTIVE);
float gCameraFov = 45.0f;

std::shared_ptr<Program> gProgram;
shared_ptr<BoxRenderObject> gBoxRenderer;

RenderNode gBoxNode1;

std::unordered_map<int, bool> gPressedKeys = {};
//-------------------------

Engine engine(1024, 768, "TakeOne");

int main()
{

    Init(engine);

    engine.SetUpdateCallback(Update);
    engine.SetDrawCallback(Draw);

    engine.Run();

    return 0;
}

void Init(Engine& pEngine)
{
    SetupCamera(pEngine);

    SetupBoxRenderer();

    gBoxNode1.SetRenderObject(gBoxRenderer);
    gBoxNode1.GetTransform().SetScale(glm::vec3(0.1f));

    pEngine.GetInput().SetCursorMode(GLFW_CURSOR_DISABLED);

    //mouse
    engine.GetInput().MousePosAction(
    [](double pXPos, double pYPos)
    {
        static float mouseSpeed = 0.03;
        static float horizontalAngle = 0;
        static float verticalAngle = 0;

        static double oldX = pXPos, oldY = pYPos;

        horizontalAngle -= mouseSpeed * float( pXPos - oldX) * 0.016;
        verticalAngle   -= mouseSpeed * float( pYPos - oldY) * 0.016;

        gCamera.SetAngleAxis(horizontalAngle, glm::vec3(0, 1, 0));
        gCamera.Rotate(verticalAngle, glm::vec3(1,0,0));

        oldX = pXPos;
        oldY = pYPos;
    });

    //keyboard
    pEngine.GetInput().KeyboardAction(
    [](int pKey, int /*pScancode*/, int pAction, int /*pMods*/)
    {
        if(pAction == GLFW_RELEASE)
            gPressedKeys[pKey] = false;
        else if(pAction == GLFW_PRESS)
            gPressedKeys[pKey] = true;
    });
}

void Update(double pDt)
{
    gCamera.SetPerspective(glm::radians(gCameraFov), 4.0f / 3.0f, 0.1f, 100000.0f);

    UpdateKeyInput(engine, 0.016);
}

void Draw()
{
    gBoxNode1.GetRenderObject()->GetMaterial().SetShaderParam("camera", gCamera.GetViewProjectionMatrix());
    gBoxNode1.SendModelMatrix();

    gBoxNode1.GetRenderObject()->Render();
}

void SetupBoxRenderer()
{
    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    gProgram = std::shared_ptr<Program>(std::move(defaultRes.UberShaderProgram()));

    gBoxRenderer = std::make_shared<BoxRenderObject>(gProgram);

    Texture diffuseTx(SampleUtil::RES_FOLDER + "textures/container2.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);
    Texture specularTx(SampleUtil::RES_FOLDER + "textures/container2_specular.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);

    gBoxRenderer->GetMaterial().SetTexture(std::move(diffuseTx));
    gBoxRenderer->GetMaterial().SetTexture(std::move(specularTx));

    //textures
    gBoxRenderer->GetMaterial().SetShaderParam("material.diffuse",  0);
    gBoxRenderer->GetMaterial().SetShaderParam("material.specular", 1);
}

void SetupCamera(Engine& pEngine)
{
    gCamera.SetClearColor(glm::vec4(63.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f, 1.0));
    gCamera.SetPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

    pEngine.GetInput().MouseScrollAction([](double /*xoffset*/, double yoffset)
    {
        auto tempFov = gCameraFov+yoffset*-1;
        if(tempFov > 0 && tempFov < 120)
            gCameraFov = tempFov;
    });
}

void UpdateKeyInput(Engine& pEngine, double pDt)
{
    static int cursorMode = GLFW_CURSOR_DISABLED;
    static float speed = 2;

    static glm::vec3 camPos(0.0f, -5.0f, 5.0f);

    //catch the release of M key
    static bool key_m_before = gPressedKeys[GLFW_KEY_M];
    if (!gPressedKeys[GLFW_KEY_M] && key_m_before){

        cursorMode = (cursorMode == GLFW_CURSOR_DISABLED)
                ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;

        pEngine.GetInput().SetCursorMode(cursorMode);
    }
    key_m_before = gPressedKeys[GLFW_KEY_M];

    if (gPressedKeys[GLFW_KEY_W]){
        camPos += gCamera.GetFrontDir() * speed * (float)pDt;
    }

    if (gPressedKeys[GLFW_KEY_S]){
        camPos -= gCamera.GetFrontDir() * speed * (float)pDt;
    }

    if (gPressedKeys[GLFW_KEY_D]){
        camPos += gCamera.GetRightDir() * speed * (float)pDt;
    }

    if (gPressedKeys[GLFW_KEY_A]){
        camPos -= gCamera.GetRightDir() * speed * (float)pDt;
    }

    if (gPressedKeys[GLFW_KEY_Q]){
        camPos -= gCamera.GetUpDir() * speed * (float)pDt;
    }

    if (gPressedKeys[GLFW_KEY_E]){
        camPos += gCamera.GetUpDir() * speed * (float)pDt;
    }

    if (gPressedKeys[GLFW_KEY_R]){
        //colorProgram->Reload();
        gProgram->Reload();
    }

    gCamera.GetTransform().SetPosition(camPos);

}
