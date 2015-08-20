#include "GL/glew.h"
#include "Engine.h"
//TODO: remove Triangle example
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>
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

    auto textureMapProgram = std::shared_ptr<Program>(std::move(res.SimpleTextureProgram()));
    //auto colorMapProgram = std::make_shared<TakeOne::Program>(RES_FOLDER + "/shaders/SimpleColor/vertex.glsl", RES_FOLDER + "/shaders/SimpleColor/fragment.glsl");

    auto boxRender = std::make_shared<TakeOne::BoxRenderObject>(textureMapProgram);
    boxRender->GetMaterial().SetTexture(TakeOne::Texture(RES_FOLDER + "/objects/Castle/th_portugal_edit-lt.jpg", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS));
    boxRender->GetMaterial().SetShaderParam("u_shininess", 0.f);
    boxRender->GetMaterial().SetShaderParam("u_color_specular", glm::vec4(1.0f));
    boxRender->GetMaterial().SetShaderParam("u_textures_count", 1);

    TakeOne::RenderNode box(boxRender);
    TakeOne::RenderNode box2(boxRender);
    TakeOne::RenderNode box3(boxRender);

    auto planeRender = std::make_shared<TakeOne::PlaneRenderObject>(textureMapProgram);
    planeRender->GetMaterial().SetTexture(TakeOne::Texture(RES_FOLDER + "/objects/Castle/window_withstone2.jpg", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS));
    TakeOne::RenderNode plane(planeRender);

    auto sphereRender = std::make_shared<TakeOne::SphereRenderObject>(textureMapProgram, 3.0f, 100, 100);
    sphereRender->GetMaterial().SetTexture(TakeOne::Texture(RES_FOLDER + "/objects/Castle/th_portugal_edit-lt.jpg", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS));
    sphereRender->GetMaterial().SetShaderParam("u_shininess", 0.5f);
    sphereRender->GetMaterial().SetShaderParam("u_color_specular", glm::vec4(1.0f));
    sphereRender->GetMaterial().SetShaderParam("u_textures_count", 1);
    TakeOne::RenderNode sphere(sphereRender);

    Light light;
    light.position = glm::vec3(0.0f, 10.0f, -10.0f);
    light.intensities = glm::vec3(2.8f, 2.8f, 2.6f);
    light.attenuation = 0.01f;
    light.ambientCoefficient = 0.05f;

    TakeOne::CameraNode camera(TakeOne::CameraType::PERSPECTIVE);
    camera.SetClearColor(glm::vec4(63.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f, 1.0));
    camera.SetPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

    box.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
    box2.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
    box3.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
    plane.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
    sphere.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());

    plane.GetTransform().SetPosition(glm::vec3(0.0f, 2.0f, 4.0f));
    plane.GetTransform().SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
    plane.ApplyTransformation("model");
    sphere.ApplyTransformation("model");

    box.ApplyTransformation("model");
    box.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
    box.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
    box.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
    box.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);

    box2.GetTransform().SetPosition(glm::vec3(17.0f));
    box2.GetTransform().SetScale(glm::vec3(2.0f));
    box2.ApplyTransformation("model");
    box2.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
    box2.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
    box2.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
    box2.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);

    box3.GetTransform().SetPosition(glm::vec3(3.0f, 5.0f, 10.0f));
    box3.GetTransform().SetScale(glm::vec3(2.0f, .5f, .5f));
    box3.GetTransform().SetRotation(glm::angleAxis(glm::pi<float>()/6.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
    box3.ApplyTransformation("model");
    box3.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
    box3.GetRenderObject()->GetMaterial().SetShaderParam("light.intensities", light.intensities);
    box3.GetRenderObject()->GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
    box3.GetRenderObject()->GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);

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

        static std::unordered_map<int, bool> pressedKeys = {};

        engine.GetInput().KeyboardAction(
        [&](int pKey, int /*pScancode*/, int pAction, int /*pMods*/)
        {
            if(pAction == GLFW_RELEASE)
                pressedKeys[pKey] = false;
            else if(pAction == GLFW_PRESS)
                pressedKeys[pKey] = true;
        });

        camera.SetPerspective(glm::radians(cameraFov), 4.0f / 3.0f, 0.1f, 100000.0f);

        static glm::vec3 camPos(0.0f, -5.0f, 5.0f);

        //catch the release of M key
        static bool key_m_before = pressedKeys[GLFW_KEY_M];
        if (!pressedKeys[GLFW_KEY_M] && key_m_before){

            cursorMode = (cursorMode == GLFW_CURSOR_DISABLED)
                    ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;

            engine.GetInput().SetCursorMode(cursorMode);
        }
        key_m_before = pressedKeys[GLFW_KEY_M];

        if (pressedKeys[GLFW_KEY_W]){
            camPos += camera.GetFrontDir() * speed;
        }

        if (pressedKeys[GLFW_KEY_S]){
            camPos -= camera.GetFrontDir() * speed;
        }

        if (pressedKeys[GLFW_KEY_D]){
            camPos += camera.GetRightDir() * speed;
        }

        if (pressedKeys[GLFW_KEY_A]){
            camPos -= camera.GetRightDir() * speed;
        }

        if (pressedKeys[GLFW_KEY_Q]){
            camPos -= camera.GetUpDir() * speed;
        }

        if (pressedKeys[GLFW_KEY_E]){
            camPos += camera.GetUpDir() * speed;
        }

        if (pressedKeys[GLFW_KEY_R]){
            //colorProgram->Reload();
            textureMapProgram->Reload();
        }

        camera.GetTransform().SetPosition(camPos);

        light.position.x = sin(lightPos) * 50;
        light.position.z = cos(lightPos) * 50;

        box.GetTransform().SetPosition(light.position);

        box.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box.ApplyTransformation("model");
        box.GetRenderObject()->Render();

        box2.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box2.ApplyTransformation("model");
        box2.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
        box2.GetRenderObject()->Render();

        box3.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box3.ApplyTransformation("model");
        box3.GetRenderObject()->GetMaterial().SetShaderParam("light.position", light.position);
        box3.GetRenderObject()->Render();

        plane.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        plane.GetRenderObject()->Render();

        sphere.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        sphere.GetRenderObject()->Render();

        engine.Update();
    }

    return 0;
}
