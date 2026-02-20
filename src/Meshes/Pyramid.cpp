#include "Meshes/Pyramid.h"

Mesh CreatePyramid()
{
    std::vector<float> vertices = {
        -0.5f,0.0f, 0.5f,  0.83f,0.70f,0.44f, 0.0f,0.0f,
        -0.5f,0.0f,-0.5f,  0.83f,0.70f,0.44f, 5.0f,0.0f,
         0.5f,0.0f,-0.5f,  0.83f,0.70f,0.44f, 0.0f,0.0f,
         0.5f,0.0f, 0.5f,  0.83f,0.70f,0.44f, 5.0f,0.0f,
         0.0f,0.8f, 0.0f,  0.92f,0.86f,0.76f, 2.5f,5.0f
    };

    std::vector<unsigned int> indices = {
        0,1,2,
        0,2,3,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };

    return Mesh(vertices, indices);
}