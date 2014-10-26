#include "GL/glew.h"
#include "Engine.h"
//TODO: remove Triangle example
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Program.h"
#include "Mesh.h"
#include "Log.h"

#include "Raster.h"

using namespace std;

int main(void)
{
    TakeOne::Engine engine(800, 600, "TakeOne");

    TakeOne::Mesh mesh;
    TakeOne::Vertex v1;
    std::vector<TakeOne::Vertex> v;
    v1.position = glm::vec3(-1.0f, -1.0f, 0.0f);
    v1.color = glm::vec3(1.0f, 0.0f, 0.0f);
    v.push_back(v1);

    v1.position = glm::vec3(1.0f, -1.0f, 0.0f);
    v1.color = glm::vec3(0.0f, 1.0f, 0.0f);
    v.push_back(v1);

    v1.position = glm::vec3(0.0f,  1.0f, 0.0f);
    v1.color = glm::vec3(0.0f, 0.0f, 1.0f);
    v.push_back(v1);

    std::vector<unsigned int> i = {0, 1, 2};

    TakeOne::bitset_vf b;
    b.set((unsigned int)TakeOne::VertexFormat::POSITION);
    b.set((unsigned int)TakeOne::VertexFormat::COLOR);

    mesh.Setup(std::move(v), std::move(i), b);

    TakeOne::Program program("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    glClearColor(0.0, 0.2, 0.5, 1.0);


    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
// Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
// Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);  // Changes for each model !
// Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around


    long long it = 0;
	while (!engine.ShouldClose())
	{
        it++;
        if(it > 100) //reload shader every 100 iterrations; to be removed!!
        {
            program.Reload();
            it = 0;
        }
        // Use our shader
        program.Use();

        // Get a handle for our "MVP" uniform.
// Only at initialisation time.
        GLint MatrixID = program.GetUniformLocation("MVP");

// Send our transformation to the currently bound shader,
// in the "MVP" uniform
// For each model you render, since the MVP will be different (at least the M part)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 1rst attribute buffer : vertices

        mesh.Render();

        engine.Update();
	}

	return 0;
}