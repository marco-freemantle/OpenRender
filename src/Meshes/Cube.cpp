#include "Meshes/Cube.h"

Mesh CreateCube()
{
    std::vector<float> vertices = {
        // position       // color          // texcoord
        -0.5f,-0.5f,-0.5f, 1,0,0, 0,0,
         0.5f,-0.5f,-0.5f, 0,1,0, 1,0,
         0.5f, 0.5f,-0.5f, 0,0,1, 1,1,
        -0.5f, 0.5f,-0.5f, 1,1,0, 0,1,
        -0.5f,-0.5f, 0.5f, 1,0,1, 0,0,
         0.5f,-0.5f, 0.5f, 0,1,1, 1,0,
         0.5f, 0.5f, 0.5f, 1,1,1, 1,1,
        -0.5f, 0.5f, 0.5f, 0,0,0, 0,1
    };

    std::vector<unsigned int> indices = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        0,1,5, 5,4,0,
        2,3,7, 7,6,2,
        1,2,6, 6,5,1,
        3,0,4, 4,7,3
    };

    return Mesh(vertices, indices);
}