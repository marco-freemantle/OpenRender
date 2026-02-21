#include "Renderer/Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(const std::vector<float>& vertices,
           const std::vector<unsigned int>& indices)
    : vbo(vertices.data(), vertices.size() * sizeof(float)),
      ebo(indices.data(), indices.size() * sizeof(unsigned int))
{
    indexCount = static_cast<GLsizei>(indices.size());

    vao.Bind();
    vbo.Bind();
    ebo.Bind();

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao.Unbind();
}

void Mesh::Draw(Material* material)
{
    material->Use();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Mesh::Delete()
{
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}