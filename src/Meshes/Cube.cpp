#include "Meshes/Cube.h"

Mesh CreateCube()
{
    std::vector<float> vertices = {
        // Position                  // TexCoord
        // Back face
        -0.5f, -0.5f, -0.5f,         0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,         1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,         0.0f, 1.0f,

        // Front face
        -0.5f, -0.5f,  0.5f,         0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,         1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,         1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,         0.0f, 1.0f,

        // Left face
        -0.5f,  0.5f,  0.5f,         1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,         1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,         0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,         0.0f, 0.0f,

        // Right face
        0.5f,  0.5f,  0.5f,         1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,         0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,         0.0f, 0.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,         0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,         1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,         1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,         0.0f, 0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,         0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,         1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,         1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,         0.0f, 0.0f,
    };

    std::vector<unsigned int> indices = {
        0,  1,  2,  2,  3,  0,  // Back
        4,  5,  6,  6,  7,  4,  // Front
        8,  9,  10, 10, 11, 8,  // Left
        12, 13, 14, 14, 15, 12, // Right
        16, 17, 18, 18, 19, 16, // Bottom
        20, 21, 22, 22, 23, 20  // Top
    };

    return Mesh(vertices, indices);
}