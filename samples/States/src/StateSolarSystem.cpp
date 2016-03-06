#include "StateSolarSystem.h"
#include "Primitives.h"
#include "DefaultRes.h"

StateSolarSystem::StateSolarSystem(Engine *pEngine)
    : StateSample(pEngine)
{
    mCameraMoveSpeed = 1.5;

    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    mProgram = std::shared_ptr<Program>(std::move(defaultRes.SimpleTextureProgram()));

    mPlanets =
    {
        {"Sky",     PlanetProp{"Sky",     "stars_milkyway.jpg",           10000, 0,   0.0,    0,     0, 0}},
        {"Sun",     PlanetProp{"Sun",     "texture_sun.jpg",              60,    0,   0.0,    0,     0, 0}}, //the real size is 277 the size of mercury
        {"Mercury", PlanetProp{"Mercury", "texture_mercury.jpg",          2,     80,  0.0125, 0.002, 0, 0}},
        {"Venus",   PlanetProp{"Venus",   "texture_venus_atmosphere.jpg", 3,     100, 0.008,  -.01,  0, 0}},
        {"Earth",   PlanetProp{"Earth",   "texture_earth_clouds.jpg",     3.3,   140, 0.01,   .02,   0, 0}},
        {"Moon",    PlanetProp{"Moon",    "texture_moon.jpg",             1,     7,   0.045,  .025,  0, 0}},
        {"Mars",    PlanetProp{"Mars",    "texture_mars.jpg",             2.9,   180, 0.012,  .02,   0, 0}},
        {"Jupiter", PlanetProp{"Jupiter", "texture_jupiter.jpg",          14.4,  300, 0.013,  .071,  0, 0}},
        {"Saturn",  PlanetProp{"Saturn",  "texture_saturn.jpg",           12,    400, 0.011,  .07,   0, 0}},
        {"Uranus",  PlanetProp{"Uranus",  "texture_uranus.jpg",           8.2,   550, 0.007,  -.05,  0, 0}},
        {"Neptune", PlanetProp{"Neptune", "texture_neptune.jpg",          6.88,  700, 0.009,  .04,   0, 0}}
    };

    for(const auto& planet : mPlanets)
        SetupNode(planet.second);

     mCamera.GetTransform()->SetPosition(vec3(0, 0, 300));

     mObjects["Mercury"].back()->GetTransform()->SetParent(&mTransformations["Mercury"]);
     mObjects["Venus"].back()->GetTransform()->SetParent(&mTransformations["Venus"]);
     mObjects["Earth"].back()->GetTransform()->SetParent(&mTransformations["Earth"]);
     mObjects["Moon"].back()->GetTransform()->SetParent(&mTransformations["Moon"]);
     mObjects["Earth"].back()->GetTransform()->AddChild(&mTransformations["Moon"]);
     mObjects["Mars"].back()->GetTransform()->SetParent(&mTransformations["Mars"]);
     mObjects["Jupiter"].back()->GetTransform()->SetParent(&mTransformations["Jupiter"]);
     mObjects["Saturn"].back()->GetTransform()->SetParent(&mTransformations["Saturn"]);
     mObjects["Uranus"].back()->GetTransform()->SetParent(&mTransformations["Uranus"]);
     mObjects["Neptune"].back()->GetTransform()->SetParent(&mTransformations["Neptune"]);
}

void StateSolarSystem::Enter()
{
    StateSample::Enter();

    glDisable(GL_CULL_FACE);
}

void StateSolarSystem::Exit()
{
    StateSample::Enter();

    glEnable(GL_CULL_FACE);
}

void StateSolarSystem::Update()
{
    StateSample::Update();

    for(const auto& obj : mObjects)
    {
        obj.second.back()->GetTransform()->SetRotation(angleAxis(mPlanets[obj.first].RevAcc, vec3(0, 1, 0)));
        mPlanets[obj.first].RevAcc += mPlanets[obj.first].RevSpeed;

        mTransformations[obj.first].SetRotation(angleAxis(mPlanets[obj.first].RotAcc, vec3(0, 1, 0)));
        mPlanets[obj.first].RotAcc += mPlanets[obj.first].RotSpeed;
    }
}

void StateSolarSystem::HandleEvents()
{
    StateSample::HandleEvents();

    static auto currPlanet = mObjects.begin();

    static bool key_p_before = mPressedKeys[GLFW_KEY_P];
    if (!mPressedKeys[GLFW_KEY_P] && key_p_before){

        mCamera.GetTransform()->SetParent((*currPlanet).second.back()->GetTransform());
        mCamera.GetTransform()->SetPosition(vec3(0, 0, mPlanets[(*currPlanet).first].Radius * 2 + 30));

        currPlanet++;
        if(currPlanet == mObjects.end())
            currPlanet = mObjects.begin();
    }
    key_p_before = mPressedKeys[GLFW_KEY_P];

    static bool key_o_before = mPressedKeys[GLFW_KEY_P];
    if (!mPressedKeys[GLFW_KEY_O] && key_o_before){
        mCamera.GetTransform()->SetParent(nullptr);
        mCamera.GetTransform()->SetPosition(vec3(0, 0, 300));
    }
    key_o_before = mPressedKeys[GLFW_KEY_O];
}

void StateSolarSystem::SetupNode(const PlanetProp& pPlanet)
{
    auto sphereNode = make_unique<RenderNode>(make_shared<SphereRenderObject>(mProgram, pPlanet.Radius, 100, 100));
    Texture diffuseTx(SampleUtil::RES_FOLDER + "textures/SolarSystem/" + pPlanet.Texture, Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);
    sphereNode->GetRenderObject()->GetMaterial().SetTexture(std::move(diffuseTx));
    sphereNode->GetTransform()->SetPosition(vec3(pPlanet.Distance, 0, 0));

    AddObject(pPlanet.Name, move(sphereNode));
}
