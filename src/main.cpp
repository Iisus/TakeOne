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
int main(void)
{
    TakeOne::Engine engine(800, 600, "TakeOne");

    TakeOne::RenderObject duck;//, teapot1, teapot2, teapot3;
    //teapot1.Load("../res/meshes/Teapot01.t1o");
    //teapot2.Load("../res/meshes/Teapot02.t1o");
    //teapot3.Load("../res/meshes/Teapot03.t1o");

    //load program
    std::unique_ptr<TakeOne::Program> program(new TakeOne::Program("../res/shaders/vertex.glsl", "../res/shaders/fragment.glsl"));
    //load texture

    duck.GetMaterial().SetProgram(std::move(program));

    duck.GetMaterial().SetTexture("u_texture", TakeOne::Texture("../res/textures/duckCM.tga", TakeOne::Texture::INVERT_Y));

    duck.Load("../res/meshes/duck.t1o");

    glClearColor(63.0f/255.0f, 75.0f/255.0f, 82.0f/255.0f, 1.0);
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = static_cast<glm::mat4>(glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f));
// Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3(30,40,30), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
// Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::scale(
            glm::mat4(1.0f),
            glm::vec3(0.15f));
// Our ModelViewProjection : multiplication of our 3 matrices

    long long it = 0;


    // Get a handle for our "MVP" uniform.
// Only at initialisation time.
    //GLint MatrixID = program.GetUniformLocation("MVP");

// Send our transformation to the currently bound shader,
// in the "MVP" uniform
// For each model you render, since the MVP will be different (at least the M part)
    //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glm::mat4 MVP        = static_cast<glm::mat4>((Projection * View * Model)); // Remember, matrix multiplication is the other way around

    duck.GetMaterial().SetShaderParam("MVP", MVP);

    glm::vec3 col(0.0, 1.0, 0.0);
    duck.GetMaterial().SetShaderParam("color", col);

	while (!engine.ShouldClose())
	{

        it++;
        if(it > 100) //reload shader every 100 iterrations; to be removed!!
        {
            duck.GetMaterial().Reload();
            it = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 1rst attribute buffer : vertices

        glUniformMatrix4fv(1, 1, GL_FALSE, &MVP[0][0]);
        duck.Render();
        //teapot1.Render();
        //teapot2.Render();
        //teapot3.Render();

        engine.Update();
	}

	return 0;
}
