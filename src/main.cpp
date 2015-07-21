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

#include "Raster.h"

#include "RenderNode.h"
#include "CameraNode.h"

#include "BoxRenderObject.h"

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

float cameraFov = 45.0f;

void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset)
{
    auto tempFov = cameraFov+yoffset*-1;
    if(tempFov > 0 && tempFov < 120)
        cameraFov = tempFov;
}

using namespace TakeOne;

int main(void)
{
    TakeOne::Engine engine(1024, 768, "TakeOne");

    auto textureMapProgram = std::make_shared<TakeOne::Program>("../res/shaders/SimpleTextureMap/vertex.glsl", "../res/shaders/SimpleTextureMap/fragment.glsl");

    auto boxRender = std::make_shared<TakeOne::BoxRenderObject>(textureMapProgram);
    boxRender->GetMaterial().SetTexture(TakeOne::Texture("../res/objects/Castle/est10.jpg", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS));

    TakeOne::RenderNode box(boxRender);
    TakeOne::RenderNode box2(boxRender);
    TakeOne::RenderNode box3(boxRender);

    Light light;
    light.position = glm::vec3(0.0f, 100.0f, -10.0f);
    light.intensities = glm::vec3(0.8f, 0.8f, 0.8f) * 600.0f;
    light.attenuation = 0.01f;
    light.ambientCoefficient = 0.0001f;

    TakeOne::CameraNode camera(TakeOne::CameraType::PERSPECTIVE);
    camera.SetClearColor(glm::vec4(63.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f, 1.0));
    camera.SetPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

    box.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
    box2.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
    box3.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());

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

    float speed = 0.01f; // 3 units / second
    float horizontalAngle = 0;
    float verticalAngle = 0;

    glfwSetScrollCallback(engine.GetWindow(), scroll_callback);

    while (!engine.ShouldClose())
    {
        lightPos+=0.001;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 1rst attribute buffer : vertices

        float mouseSpeed = 0.0005f;
        double xPos, yPos;

        static bool useMouseInput = true;

        if(useMouseInput)
        {
            glfwGetCursorPos(engine.GetWindow(), &xPos, &yPos);
            glfwSetCursorPos(engine.GetWindow(), 1024/2, 768/2);
        }

        static unsigned int timeSample = 0;
        if (timeSample++ > 100 && glfwGetKey(engine.GetWindow(), GLFW_KEY_M ) == GLFW_PRESS)
        {
            timeSample = 0;
            mouseSpeed = 0;
            xPos = 1024/2;
            yPos = 768/2;
            useMouseInput = !useMouseInput;
        }

        horizontalAngle -= mouseSpeed * float( xPos - 1024/2 );
        verticalAngle   -= mouseSpeed * float( yPos - 768/2 );

        camera.SetAngleAxis(horizontalAngle, glm::vec3(0, 1, 0));
        camera.Rotate(verticalAngle, glm::vec3(1,0,0));

        camera.SetPerspective(glm::radians(cameraFov), 4.0f / 3.0f, 0.1f, 100000.0f);

        static glm::vec3 camPos(0.0f, -5.0f, 5.0f);

        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_W ) == GLFW_PRESS){
            camPos += camera.GetFrontDir() * speed;
        }

        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_S ) == GLFW_PRESS){
            camPos -= camera.GetFrontDir() * speed;
        }

        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_D ) == GLFW_PRESS){
            camPos += camera.GetRightDir() * speed;
        }

        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_A ) == GLFW_PRESS){
            camPos -= camera.GetRightDir() * speed;
        }

        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_Q ) == GLFW_PRESS){
            camPos -= camera.GetUpDir() * speed;
        }

        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_E ) == GLFW_PRESS){
            camPos += camera.GetUpDir() * speed;
        }

        if (glfwGetKey(engine.GetWindow(), GLFW_KEY_R ) == GLFW_PRESS){
            //colorProgram->Reload();
            textureMapProgram->Reload();
        }

        camera.GetTransform().SetPosition(camPos);

//        light.position.x = sin(lightPos) * 200;
//        light.position.z = cos(lightPos) * 200;
        box.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box.ApplyTransformation("model");
        box.GetRenderObject()->Render();

        box2.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box2.ApplyTransformation("model");
        box2.GetRenderObject()->Render();

        box3.GetRenderObject()->GetMaterial().SetShaderParam("camera", camera.GetViewProjectionMatrix());
        box3.ApplyTransformation("model");
        box3.GetRenderObject()->Render();

        engine.Update();
    }

    return 0;
}
