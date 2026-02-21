#include "Meshes/Pyramid.h"

Mesh CreatePyramid()
{
    std::vector<float> vertices = {
        // Position              // TexCoord
        // Bottom Face (Square)
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, 1.0f,

        // Front Face (Triangle)
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
        0.0f,  0.5f,  0.0f,     0.5f, 1.0f, // Peak

        // Right Face (Triangle)
        0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
        0.0f,  0.5f,  0.0f,     0.5f, 1.0f, // Peak

        // Back Face (Triangle)
        0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
        0.0f,  0.5f,  0.0f,     0.5f, 1.0f, // Peak

        // Left Face (Triangle)
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
        0.0f,  0.5f,  0.0f,     0.5f, 1.0f  // Peak
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,  2, 3, 0,   // Base
        4, 5, 6,             // Front
        7, 8, 9,             // Right
        10, 11, 12,          // Back
        13, 14, 15           // Left
    };

    return Mesh(vertices, indices);
}