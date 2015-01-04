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

#include "Transform.h"

struct Light {
    glm::vec3 position;
    glm::vec3 intensities; //a.k.a. the color of the light
    float attenuation; //new this article
    float ambientCoefficient; //new this article
};

int main(void)
{
    TakeOne::Engine engine(1024, 768, "TakeOne");

    std::vector <TakeOne::RenderObject> StreetEnv(30);
    TakeOne::RenderObject duck;

    //load program
    std::shared_ptr<TakeOne::Program> textureMapProgram(new TakeOne::Program("../res/shaders/SimpleTextureMap/vertex.glsl", "../res/shaders/SimpleTextureMap/fragment.glsl"));
    for(unsigned int i=0; i<27; i++)
    {
        StreetEnv[i].GetMaterial().SetProgram(textureMapProgram);
    }
    //load program
    std::shared_ptr<TakeOne::Program> colorProgram(new TakeOne::Program("../res/shaders/SimpleColor/vertex.glsl", "../res/shaders/SimpleColor/fragment.glsl"));
    for(unsigned int i=27; i<30; i++)
    {
        StreetEnv[i].GetMaterial().SetProgram(colorProgram);
    }


    StreetEnv[0].Load("../res/objects/StreetEnv/g City_building_001");
    StreetEnv[1].Load("../res/objects/StreetEnv/g City_building_004");
    StreetEnv[2].Load("../res/objects/StreetEnv/g City_building_007");
    StreetEnv[3].Load("../res/objects/StreetEnv/g City_building_008");
    StreetEnv[4].Load("../res/objects/StreetEnv/g City_building_010");
    StreetEnv[5].Load("../res/objects/StreetEnv/g City_building_011");
    StreetEnv[6].Load("../res/objects/StreetEnv/g City_building_013");
    StreetEnv[7].Load("../res/objects/StreetEnv/g City_building_014");
    StreetEnv[8].Load("../res/objects/StreetEnv/g City_building_016");
    StreetEnv[9].Load("../res/objects/StreetEnv/g City_building_017");
    StreetEnv[10].Load("../res/objects/StreetEnv/g City_building_022");
    StreetEnv[11].Load("../res/objects/StreetEnv/g City_building_023");
    StreetEnv[12].Load("../res/objects/StreetEnv/g City_building_024");
    StreetEnv[13].Load("../res/objects/StreetEnv/g City_building_026");
    StreetEnv[14].Load("../res/objects/StreetEnv/g City_building_028");
    StreetEnv[15].Load("../res/objects/StreetEnv/g City_building_030");
    StreetEnv[16].Load("../res/objects/StreetEnv/g City_building_031");
    StreetEnv[17].Load("../res/objects/StreetEnv/g City_building_032");
    StreetEnv[18].Load("../res/objects/StreetEnv/g City_building_033");
    StreetEnv[19].Load("../res/objects/StreetEnv/g City_building_034");
    StreetEnv[20].Load("../res/objects/StreetEnv/g City_building_035");
    StreetEnv[21].Load("../res/objects/StreetEnv/g City_building_036");
    StreetEnv[22].Load("../res/objects/StreetEnv/g City_building_037");
    StreetEnv[23].Load("../res/objects/StreetEnv/g City_building_038");
    StreetEnv[24].Load("../res/objects/StreetEnv/g City_building_039");
    StreetEnv[25].Load("../res/objects/StreetEnv/g City_building_040");
    StreetEnv[26].Load("../res/objects/StreetEnv/g City_building_041");
    StreetEnv[27].Load("../res/objects/StreetEnv/g Line002");
    StreetEnv[28].Load("../res/objects/StreetEnv/g Object010");
    StreetEnv[29].Load("../res/objects/StreetEnv/g Plane001");

    duck.GetMaterial().SetProgram(textureMapProgram);
    duck.Load("../res/objects/Duck/");

    glClearColor(63.0f/255.0f, 75.0f/255.0f, 82.0f/255.0f, 1.0);
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
    glm::mat4 Projection = static_cast<glm::mat4>(glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f));
// Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3(40,40,40), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

// Our ModelViewProjection : multiplication of our 3 matrices

    long long it = 0;


    // Get a handle for our "MVP" uniform.
// Only at initialisation time.
    //GLint MatrixID = program.GetUniformLocation("MVP");

// Send our transformation to the currently bound shader,
// in the "MVP" uniform
// For each model you render, since the MVP will be different (at least the M part)
    //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glm::mat4 Camera        = static_cast<glm::mat4>((Projection * View)); // Remember, matrix multiplication is the other way around


    Light light;
    light.position = glm::vec3(-8.0f, 8.0f, 10.0f);
    light.intensities = glm::vec3(0.7f, 0.5f, 0.3f)*10.0f;
    light.attenuation = 0.01f;
    light.ambientCoefficient = 0.001f;

    TakeOne::Transform streetTransform;
    streetTransform.SetScale(glm::vec3(0.8f));

    for(auto &obj : StreetEnv)
    {
        obj.GetMaterial().SetShaderParam("camera", Camera);
        obj.GetMaterial().SetShaderParam("model", streetTransform.GetTransform());

        obj.GetMaterial().SetShaderParam("light.position", light.position);
        obj.GetMaterial().SetShaderParam("light.intensities", light.intensities);
        obj.GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
        obj.GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);
    }

    TakeOne::Transform duckTransform;
    duckTransform.SetParent(&streetTransform);

    duckTransform.SetPosition(glm::vec3(30, 0, 0));
    duckTransform.SetScale(glm::vec3(0.05f));

    duck.GetMaterial().SetShaderParam("camera", Camera);
    duck.GetMaterial().SetShaderParam("model", duckTransform.GetTransform());
    duck.GetMaterial().SetShaderParam("light.position", light.position);
    duck.GetMaterial().SetShaderParam("light.intensities", light.intensities);
    duck.GetMaterial().SetShaderParam("light.attenuation", light.attenuation);
    duck.GetMaterial().SetShaderParam("light.ambientCoefficient", light.ambientCoefficient);

    double lightPos=0;
	while (!engine.ShouldClose())
	{
        lightPos+=0.001;
        it++;
        if(it > 100) //reload shader every 100 iterrations; to be removed!!
        {
            for(auto& obj : StreetEnv)
            {

                obj.GetMaterial().Reload();
            }
            it = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 1rst attribute buffer : vertices

        streetTransform.SetRotation(glm::angleAxis(static_cast<float>(lightPos), glm::vec3(0.0f, 1.0f, 0.0f)));
        duckTransform.SetPosition(glm::vec3(30.0f, (sin(lightPos)+1)*10, 0.0f));
        duckTransform.SetScale(glm::vec3((cos(lightPos*5)+1)*0.01+0.005));
        for(auto& obj : StreetEnv)
        {
            obj.GetMaterial().SetShaderParam("model", streetTransform.GetTransform());
            obj.Render();
        }

        duck.GetMaterial().SetShaderParam("model", duckTransform.GetTransform());
        duck.Render();

        engine.Update();
	}

	return 0;
}
