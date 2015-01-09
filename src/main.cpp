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
#include "CameraNode.h"

struct Light {
    glm::vec3 position;
    glm::vec3 intensities; //a.k.a. the color of the light
    float attenuation; //new this article
    float ambientCoefficient; //new this article
};

void DrawLine(glm::vec3 pStart, glm::vec3 pEnd, glm::vec3 pColor = glm::vec3(0.0f, 0.0f, 0.0f), float pWidth = 1.0f)
{
    glLineWidth(pWidth);
    glColor3fv(&pColor[0]);
    glBegin(GL_LINES);
    glVertex3fv(&pStart[0]);
    glVertex3fv(&pEnd[0]);
    glEnd();
}

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

    std::vector<TakeOne::RenderNode> ducks(1);
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

    TakeOne::CameraNode camera(TakeOne::CameraType::PERSPECTIVE);
    camera.SetClearColor(glm::vec4(63.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f, 1.0));
    camera.SetPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    //camera.SetPitch(1.0);
    camera.GetTransform().SetPosition(glm::vec3(40, 40, 40));
    camera.SetYaw(0.8);
    //camera.SetRoll(1.0);
    camera.SetPitch(-0.6);
    //camera.LookAt(glm::vec3(0, 0, 0));

    Light light;
    light.position = glm::vec3(-8.0f, 8.0f, 10.0f);
    light.intensities = glm::vec3(0.7f, 0.5f, 0.3f) * 10.0f;
    light.attenuation = 0.01f;
    light.ambientCoefficient = 0.001f;

    TakeOne::Node streetTransform;
    streetTransform.GetTransform().SetScale(glm::vec3(0.8f));

    for (auto &obj : StreetEnv)
    {
        obj.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        obj.GetRenderObject()->GetMaterial().SetShaderParam("model", streetTransform.GetTransform().GetTransformMatrix());

        obj.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
        obj.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
        obj.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
        obj.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);
    }

    for (auto &duck : ducks)
    {
        //duck.GetTransform().SetParent(&streetTransform.GetTransform());
        duck.GetTransform().SetScale(glm::vec3(0.05));
        duck.GetTransform().SetPosition(glm::vec3(0, 0, -10));
        duck.GetTransform().SetRotation(glm::angleAxis(glm::pi<float>()/2, glm::vec3(0.3f, 0.3f, 0.3f)));
        duck.ApplyTransformation("model");

        duck.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        duck.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
        duck.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
        duck.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
        duck.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);
    }

    double lightPos=0;

    float speed = 0.05f; // 3 units / second
    float mouseSpeed = 0.005f;
    float horizontalAngle = 0;
    float verticalAngle = 0;
    glm::vec3 position = glm::vec3(0.0f);

    while (!engine.ShouldClose())
	{
        lightPos+=0.001;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 1rst attribute buffer : vertices

        //streetTransform.GetTransform().SetRotation(glm::angleAxis(static_cast<float>(lightPos), glm::vec3(0.0f, 1.0f, 0.0f)));


//        double xPos, yPos;
//        glfwGetCursorPos(engine.GetWindow(), &xPos, &yPos);
//        glfwSetCursorPos(engine.GetWindow(), 1024/2, 768/2);
//        horizontalAngle += mouseSpeed * float(1024/2 - xPos );
//        verticalAngle   += mouseSpeed * float( 768/2 - yPos );
//        //camera.SetYaw(horizontalAngle*0.0174532925);
//        camera.GetTransform().SetRotation(glm::angleAxis(horizontalAngle, glm::vec3(0, 1, 0)) * glm::angleAxis(verticalAngle, glm::vec3(1, 0, 0)));
//
//        glm::vec3 direction(
//            cos(verticalAngle) * sin(horizontalAngle),
//            sin(verticalAngle),
//            cos(verticalAngle) * cos(horizontalAngle)
//        );
//
//        glm::vec3 right = glm::vec3(
//            sin(horizontalAngle - 3.14f/2.0f),
//            0,
//            cos(horizontalAngle - 3.14f/2.0f)
//        );
//
//        glm::vec3 up = glm::cross( right, direction );
//
//        // Move forward
//        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_W ) == GLFW_PRESS){
//            position -= direction * speed;
//        }
//// Move backward
//        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_S ) == GLFW_PRESS){
//            position += direction * speed;
//        }
//// Strafe right
//        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_D ) == GLFW_PRESS){
//            position -= right * speed;
//        }
//// Strafe left
//        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_A ) == GLFW_PRESS){
//            position += right * speed;
//        }
//
//        camera.GetTransform().SetPosition(position);


        float i=0;
        for(auto &duck : ducks)
        {
            //duck.GetTransform().SetPosition(glm::vec3(i++, (sin(lightPos) + 1) * 10, 0.0f));
            //duck.GetTransform().SetScale(glm::vec3((cos(lightPos * 5) + 1) * 0.01 + 0.005));
            //duck.ApplyTransformation("model");
            duck.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
            duck.GetRenderObject()->Render();
        }

        for(auto& obj : StreetEnv)
        {
            for(auto& obj1 : StreetEnv)
            {
                DrawLine(obj1.GetTransform().GetPosition(), obj.GetTransform().GetPosition());
            }
            //obj.GetTransformMatrix().SetRotation(glm::angleAxis(static_cast<float>(lightPos), glm::vec3(0.0f, 1.0f, 0.0f)));
            //obj.ApplyTransformation("model");
            //obj.GetRenderObject()->GetMaterial().SetShaderParam("model", streetTransform.GetTransformMatrix());
            obj.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
            obj.GetRenderObject()->Render();
        }

        camera.GetClearColor();

        engine.Update();
	}

	return 0;
}
