#include "GL/glew.h"
#include "Engine.h"
//TODO: remove Triangle example
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <glm/gtx/euler_angles.hpp>
#include <future>
#include "Program.h"
#include "Mesh.h"
#include "Log.h"
#include "Material.h"
#include "RenderObject.h"
#include "DefaultRes.h"

#include "Raster.h"

#include "RenderNode.h"
#include "CameraNode.h"

#include "Primitives.h"

#include "SampleUtil.h"

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

using namespace TakeOne;

int main(void)
{
    TakeOne::Engine engine(1024, 768, "TakeOne");

    DefaultRes res(RES_FOLDER);

    auto textureMapProgram = std::shared_ptr<Program>(std::move(res.UberShaderProgram()));

    auto boxRender = std::make_shared<TakeOne::BoxRenderObject>(textureMapProgram);
    TakeOne::Texture t1, t2;

    t1.LoadFromFile(RES_FOLDER + "textures/container2.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);
    t2.LoadFromFile(RES_FOLDER + "textures/container2_specular.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);

    boxRender->GetMaterial().SetTexture(std::move(t1));
    boxRender->GetMaterial().SetTexture(std::move(t2));

    //textures
    boxRender->GetMaterial().SetShaderParam("material.diffuse",  0);
    boxRender->GetMaterial().SetShaderParam("material.specular", 1);

//    boxRender->GetMaterial().SetShaderParam("u_shininess", 0.f);
//    boxRender->GetMaterial().SetShaderParam("u_color_specular", glm::vec4(1.0f));
//    boxRender->GetMaterial().SetShaderParam("u_textures_count", 1);


    TakeOne::RenderNode box(boxRender);
    TakeOne::RenderNode box2(boxRender);
    TakeOne::RenderNode box3(boxRender);

//    auto planeRender = std::make_shared<TakeOne::PlaneRenderObject>(textureMapProgram);
//    planeRender->GetMaterial().SetTexture(TakeOne::Texture(RES_FOLDER + "/objects/Castle/window_withstone2.jpg", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS));
//    TakeOne::RenderNode plane(planeRender);

//    auto sphereRender = std::make_shared<TakeOne::SphereRenderObject>(textureMapProgram, 3.0f, 100, 100);
//    sphereRender->GetMaterial().SetTexture(TakeOne::Texture(RES_FOLDER + "/objects/Castle/th_portugal_edit-lt.jpg", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS));
//    sphereRender->GetMaterial().SetShaderParam("u_shininess", 0.5f);
//    sphereRender->GetMaterial().SetShaderParam("u_color_specular", glm::vec4(1.0f));
//    sphereRender->GetMaterial().SetShaderParam("u_textures_count", 1);
//    TakeOne::RenderNode sphere(sphereRender);

//    Light light;
//    light.position = glm::vec3(0.0f, 10.0f, -10.0f);
//    light.intensities = glm::vec3(2.8f, 2.8f, 2.6f);
//    light.attenuation = 0.01f;
//    light.ambientCoefficient = 0.05f;

    TakeOne::CameraNode camera(TakeOne::CameraType::PERSPECTIVE);
    camera.SetClearColor(glm::vec4(63.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f, 1.0));
    camera.SetPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

    box.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
    box2.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
    box3.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
//    plane.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
//    sphere.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());

//    plane.GetTransform().SetPosition(glm::vec3(0.0f, 2.0f, 4.0f));
//    plane.GetTransform().SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
//    plane.SendModelMatrix();
//    sphere.SendModelMatrix();

    box.SendModelMatrix();
//    box.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
//    box.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
//    box.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
//    box.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);

    box2.GetTransform().SetPosition(glm::vec3(17.0f));
    box2.GetTransform().SetScale(glm::vec3(2.0f));
    box2.SendModelMatrix();
//    box2.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
//    box2.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
//    box2.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
//    box2.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);

    box3.GetTransform().SetPosition(glm::vec3(3.0f, 5.0f, 10.0f));
    box3.GetTransform().SetScale(glm::vec3(2.0f, .5f, .5f));
    box3.GetTransform().SetRotation(glm::angleAxis(glm::pi<float>()/6.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
    box3.SendModelMatrix();
//    box3.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
//    box3.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
//    box3.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
//    box3.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);

    double lightPos=0;

    float speed = 0.1f; // 3 units / second


    float cameraFov = 45.0f;

    engine.GetInput().MouseScrollAction([&cameraFov](double /*xoffset*/, double yoffset)
    {
        auto tempFov = cameraFov+yoffset*-1;
        if(tempFov > 0 && tempFov < 120)
            cameraFov = tempFov;
    });

    int cursorMode = GLFW_CURSOR_DISABLED;
    engine.GetInput().SetCursorMode(cursorMode);

    // Positions of the point lights
        glm::vec3 pointLightPositions[] = {
            glm::vec3( 7.0f,  2.0f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
        };

    while (!engine.ShouldClose())
    {
        lightPos+=0.001;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 1rst attribute buffer : vertices

        float mouseSpeed = 0.0005f;

        static bool useMouseInput = true;

        engine.GetInput().MousePosAction(
        [&camera, &mouseSpeed](double pXPos, double pYPos)
        {
            static float horizontalAngle = 0;
            static float verticalAngle = 0;

            static double oldX = pXPos, oldY = pYPos;

            if(useMouseInput)
            {
                horizontalAngle -= mouseSpeed * float( pXPos - oldX);
                verticalAngle   -= mouseSpeed * float( pYPos - oldY);

                camera.SetAngleAxis(horizontalAngle, glm::vec3(0, 1, 0));
                camera.Rotate(verticalAngle, glm::vec3(1,0,0));
            }

            oldX = pXPos;
            oldY = pYPos;
        });

        static int pressedKey = GLFW_KEY_UNKNOWN;

        engine.GetInput().KeyboardAction(
        [&](int pKey, int /*pScancode*/, int pAction, int /*pMods*/)
        {
            if (pKey == GLFW_KEY_M && pAction == GLFW_RELEASE)
            {
                if(cursorMode == GLFW_CURSOR_DISABLED)
                {
                    cursorMode = GLFW_CURSOR_NORMAL;
                    //useMouseInput = false;
                }
                else
                {
                    cursorMode = GLFW_CURSOR_DISABLED;
                    //useMouseInput = true;
                }

                engine.GetInput().SetCursorMode(cursorMode);
            }

            if(pKey == pressedKey && pAction == GLFW_RELEASE)
                pressedKey = GLFW_KEY_UNKNOWN;
            else if(pAction == GLFW_PRESS)
                pressedKey = pKey;
        });

        camera.SetPerspective(glm::radians(cameraFov), 4.0f / 3.0f, 0.1f, 100000.0f);

        static glm::vec3 camPos(0.0f, -5.0f, 5.0f);

        if (pressedKey == GLFW_KEY_W){
            camPos += camera.GetFrontDir() * speed;
        }

        if (pressedKey == GLFW_KEY_S){
            camPos -= camera.GetFrontDir() * speed;
        }

        if (pressedKey == GLFW_KEY_D){
            camPos += camera.GetRightDir() * speed;
        }

        if (pressedKey == GLFW_KEY_A){
            camPos -= camera.GetRightDir() * speed;
        }

        if (pressedKey == GLFW_KEY_Q){
            camPos -= camera.GetUpDir() * speed;
        }

        if (pressedKey == GLFW_KEY_E){
            camPos += camera.GetUpDir() * speed;
        }

        if (pressedKey == GLFW_KEY_R){
            //colorProgram->Reload();
            textureMapProgram->Reload();
        }

        camera.GetTransform().SetPosition(camPos);

        //light.position.x = sin(lightPos) * 50;
        //light.position.z = cos(lightPos) * 50;

        //box.GetTransform().SetPosition(light.position);

       boxRender->GetMaterial().SetShaderParam("material.shininess", 32.0f);
       // Directional light
       boxRender->GetMaterial().SetShaderParam("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
       boxRender->GetMaterial().SetShaderParam("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
       boxRender->GetMaterial().SetShaderParam("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
       boxRender->GetMaterial().SetShaderParam("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
       // Point light 1
       boxRender->GetMaterial().SetShaderParam("pointLight[0].position", pointLightPositions[0]);
       boxRender->GetMaterial().SetShaderParam("pointLight[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
       boxRender->GetMaterial().SetShaderParam("pointLight[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
       boxRender->GetMaterial().SetShaderParam("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
       boxRender->GetMaterial().SetShaderParam("pointLight[0].constantAttenuation", 1.0f);
       boxRender->GetMaterial().SetShaderParam("pointLight[0].linearAttenuation", 0.09f);
       boxRender->GetMaterial().SetShaderParam("pointLight[0].quadraticAttenuation", 0.032f);
//       // Point light 2
       boxRender->GetMaterial().SetShaderParam("pointLight[1].position", pointLightPositions[1]);
       boxRender->GetMaterial().SetShaderParam("pointLight[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
       boxRender->GetMaterial().SetShaderParam("pointLight[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
       boxRender->GetMaterial().SetShaderParam("pointLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
       boxRender->GetMaterial().SetShaderParam("pointLight[1].constantAttenuation", 1.0f);
       boxRender->GetMaterial().SetShaderParam("pointLight[1].linearAttenuation", 0.09f);
       boxRender->GetMaterial().SetShaderParam("pointLight[1].quadraticAttenuation", 0.032f);


       boxRender->GetMaterial().SetShaderParam("spotLight[0].position", glm::vec3(3.0f, 3.0f, 3.0f));
       boxRender->GetMaterial().SetShaderParam("spotLight[0].direction", glm::vec3(-0.2f, -1.0f, -0.3f));
       boxRender->GetMaterial().SetShaderParam("spotLight[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
       boxRender->GetMaterial().SetShaderParam("spotLight[0].diffuse", glm::vec3(1.0f, 0.8f, 0.8f));
       boxRender->GetMaterial().SetShaderParam("spotLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
       boxRender->GetMaterial().SetShaderParam("spotLight[0].constantAttenuation", 1.0f);
       boxRender->GetMaterial().SetShaderParam("spotLight[0].cutOff", 0.6f);
       boxRender->GetMaterial().SetShaderParam("spotLight[0].outerCutOff", 1.6f);

       boxRender->GetMaterial().SetShaderParam("spotLight[0].linearAttenuation", 0.09f);
       boxRender->GetMaterial().SetShaderParam("spotLight[0].quadraticAttenuation", 0.032f);


        box.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box.SendModelMatrix();
        box.GetRenderObject()->Render();

        box2.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box2.SendModelMatrix();
        //box2.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
        box2.GetRenderObject()->Render();

        box3.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box3.SendModelMatrix();
        //box3.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
        box3.GetRenderObject()->Render();

//        plane.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
//        plane.GetRenderObject()->Render();

//        sphere.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
//        sphere.GetRenderObject()->Render();

        engine.Update();
    }

    return 0;
}
