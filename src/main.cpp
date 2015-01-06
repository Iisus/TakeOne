#include "GL/glew.h"
#include "Engine.h"
//TODO: remove Triangle example
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Program.h"
#include "Mesh.h"
#include "Log.h"
#include "Material.h"
#include "RenderObject.h"

#include "Raster.h"

#include "RenderNode.h"

struct Light {
    glm::vec3 position;
    glm::vec3 intensities; //a.k.a. the color of the light
    float attenuation; //new this article
    float ambientCoefficient; //new this article
};

int main(void)
{
    TakeOne::Engine engine(1024, 768, "TakeOne");

    std::shared_ptr<TakeOne::Program> textureMapProgram(std::make_shared<TakeOne::Program>("../res/shaders/SimpleTextureMap/vertex.glsl", "../res/shaders/SimpleTextureMap/fragment.glsl"));

    std::vector<TakeOne::RenderNode> StreetEnv(30);
    for (auto& block : StreetEnv)
        block.SetRenderObject(std::make_shared<TakeOne::RenderObject>());

    auto duckRO = std::make_shared<TakeOne::RenderObject>();
    duckRO->GetMaterial().SetProgram(textureMapProgram);
    duckRO->Load("../res/objects/Duck/");

    std::vector<TakeOne::RenderNode> ducks(300);
    for (auto& duck : ducks)
        duck.SetRenderObject(duckRO);


    //load program
    for (unsigned int i = 0; i < 27; i++)
    {
        StreetEnv[i].GetRenderObject()->GetMaterial().SetProgram(textureMapProgram);
    }
    //load program
    std::shared_ptr<TakeOne::Program> colorProgram(std::make_shared<TakeOne::Program>("../res/shaders/SimpleColor/vertex.glsl", "../res/shaders/SimpleColor/fragment.glsl"));
    for (unsigned int i = 27; i < 30; i++)
    {
        StreetEnv[i].GetRenderObject()->GetMaterial().SetProgram(colorProgram);
    }

    StreetEnv[0].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_001");
    StreetEnv[1].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_004");
    StreetEnv[2].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_007");
    StreetEnv[3].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_008");
    StreetEnv[4].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_010");
    StreetEnv[5].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_011");
    StreetEnv[6].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_013");
    StreetEnv[7].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_014");
    StreetEnv[8].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_016");
    StreetEnv[9].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_017");
    StreetEnv[10].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_022");
    StreetEnv[11].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_023");
    StreetEnv[12].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_024");
    StreetEnv[13].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_026");
    StreetEnv[14].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_028");
    StreetEnv[15].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_030");
    StreetEnv[16].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_031");
    StreetEnv[17].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_032");
    StreetEnv[18].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_033");
    StreetEnv[19].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_034");
    StreetEnv[20].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_035");
    StreetEnv[21].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_036");
    StreetEnv[22].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_037");
    StreetEnv[23].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_038");
    StreetEnv[24].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_039");
    StreetEnv[25].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_040");
    StreetEnv[26].GetRenderObject()->Load("../res/objects/StreetEnv/g City_building_041");
    StreetEnv[27].GetRenderObject()->Load("../res/objects/StreetEnv/g Line002");
    StreetEnv[28].GetRenderObject()->Load("../res/objects/StreetEnv/g Object010");
    StreetEnv[29].GetRenderObject()->Load("../res/objects/StreetEnv/g Plane001");


    glClearColor(63.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f, 1.0);
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
    glm::mat4 Projection = static_cast<glm::mat4>(glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f));
// Camera matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(40, 40, 40), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glm::mat4 Camera = static_cast<glm::mat4>((Projection * View));


    Light light;
    light.position = glm::vec3(-8.0f, 8.0f, 10.0f);
    light.intensities = glm::vec3(0.7f, 0.5f, 0.3f) * 10.0f;
    light.attenuation = 0.01f;
    light.ambientCoefficient = 0.001f;

    TakeOne::Transform streetTransform;
    streetTransform.SetScale(glm::vec3(0.8f));

    for (auto &obj : StreetEnv)
    {
        obj.GetRenderObject()->GetMaterial().SetShaderParam("camera", Camera);
        obj.GetRenderObject()->GetMaterial().SetShaderParam("model", streetTransform.GetTransform());

        obj.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
        obj.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
        obj.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
        obj.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);
    }

    for (auto &duck : ducks)
    {
        duck.GetTransform().SetParent(&streetTransform);

        duck.GetRenderObject()->GetMaterial().SetShaderParam("camera", Camera);
        duck.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
        duck.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
        duck.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
        duck.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);
    }

    double lightPos=0;

    while (!engine.ShouldClose())
	{
        lightPos+=0.001;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 1rst attribute buffer : vertices

        streetTransform.SetRotation(glm::angleAxis(static_cast<float>(lightPos), glm::vec3(0.0f, 1.0f, 0.0f)));

        float i=0;
        for(auto &duck : ducks)
        {
            duck.GetTransform().SetPosition(glm::vec3(i++, (sin(lightPos) + 1) * 10, 0.0f));
            duck.GetTransform().SetScale(glm::vec3((cos(lightPos * 5) + 1) * 0.01 + 0.005));
            duck.ApplyTransformation("model");
            duck.GetRenderObject()->Render();
        }

        for(auto& obj : StreetEnv)
        {
            //obj.GetTransform().SetRotation(glm::angleAxis(static_cast<float>(lightPos), glm::vec3(0.0f, 1.0f, 0.0f)));
            //obj.ApplyTransformation("model");
            obj.GetRenderObject()->GetMaterial().SetShaderParam("model", streetTransform.GetTransform());
            obj.GetRenderObject()->Render();
        }

        engine.Update();
	}

	return 0;
}
