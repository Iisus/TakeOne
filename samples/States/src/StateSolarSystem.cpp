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
        PlanetProp{"Sky", "stars_milkyway.jpg", 10000, 0, 0},
        PlanetProp{"Sun", "texture_sun.jpg", 100, 0, 0}, //the real size is 277 the size of mercury
        PlanetProp{"Mercury", "texture_mercury.jpg", 1, 123.7, 0},
        PlanetProp{"Venus", "texture_venus_atmosphere.jpg", 2.41, 144.3, 0},
        PlanetProp{"Earth", "texture_earth_clouds.jpg", 2.54, 161.3, 0},
        PlanetProp{"Moon", "texture_moon.jpg",0.69, 5, 0},
        PlanetProp{"Mars", "texture_mars.jpg", 1.34, 193.4, 0},
        PlanetProp{"Jupiter", "texture_jupiter.jpg", 28.4, 419.0, 0},
        PlanetProp{"Saturn", "texture_saturn.jpg", 24, 687.2, 0},
        PlanetProp{"Uranus", "texture_uranus.jpg", 10.2, 1279.0, 0},
        PlanetProp{"Neptune", "texture_neptune.jpg", 9.88, 1943.4, 0},
    };

    for(const auto& planet : mPlanets)
        SetupNode(planet);

     mCamera.GetTransform()->SetPosition(vec3(0, 0, 800));

     mObjects["Mercury"].back()->GetTransform()->SetParent(&mSunTransform);
     mObjects["Venus"].back()->GetTransform()->SetParent(&mSunTransform);
     mObjects["Earth"].back()->GetTransform()->SetParent(&mSunTransform);
     mObjects["Moon"].back()->GetTransform()->SetParent(mObjects["Earth"].back()->GetTransform());
     mObjects["Mars"].back()->GetTransform()->SetParent(&mSunTransform);
     mObjects["Jupiter"].back()->GetTransform()->SetParent(&mSunTransform);
     mObjects["Saturn"].back()->GetTransform()->SetParent(&mSunTransform);
     mObjects["Uranus"].back()->GetTransform()->SetParent(&mSunTransform);
     mObjects["Neptune"].back()->GetTransform()->SetParent(&mSunTransform);
}

void StateSolarSystem::Update()
{
    static float angle = 0;
    angle +=0.002;
    mSunTransform.SetRotation(glm::angleAxis(angle, vec3(0, 1, 0)));

    mObjects["Earth"].back()->GetTransform()->SetRotation(glm::angleAxis(angle*100, vec3(0, 1, 0)));
}

void StateSolarSystem::SetupNode(const PlanetProp& pPlanet)
{
    auto sphereNode = make_unique<RenderNode>(make_shared<SphereRenderObject>(mProgram, pPlanet.Radius, 100, 100));
    Texture diffuseTx(SampleUtil::RES_FOLDER + "textures/SolarSystem/" + pPlanet.Texture, Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);
    sphereNode->GetRenderObject()->GetMaterial().SetTexture(std::move(diffuseTx));
    sphereNode->GetTransform()->SetPosition(vec3(pPlanet.Distance, 0, 0));


    AddObject(pPlanet.Name, move(sphereNode));
}
