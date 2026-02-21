// Renderer/Material.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
    Shader* shader = nullptr;
    Texture* texture = nullptr;
    glm::vec4 color = glm::vec4(1.0f); // fallback color if no texture

    Material() = default;
    Material(Shader* shader, Texture* texture = nullptr, glm::vec4 colour = glm::vec4(1.0f))
        : shader(shader), texture(texture), color(colour) {}

    void Use();
};