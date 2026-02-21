#pragma once
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Material.h"

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    void Draw(Material* material);
    void Delete();

    Texture* texture;

private:
    VAO vao;
    VBO vbo;
    EBO ebo;

    GLsizei indexCount;
};