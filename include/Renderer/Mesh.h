#pragma once
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    void Draw(Shader& shader);
    void Delete();

    Texture* texture;

private:
    VAO vao;
    VBO vbo;
    EBO ebo;

    GLsizei indexCount;
};