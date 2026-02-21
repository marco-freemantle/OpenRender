#include "Renderer/Material.h"

void Material::Use()
{
    shader->Activate();

    // Bind texture if present
    if (texture) {
        texture->Bind();
        glUniform1i(glGetUniformLocation(shader->ID, "useTexture"), 1);
    } else {
        glUniform1i(glGetUniformLocation(shader->ID, "useTexture"), 0);
    }

    // Set color uniform
    GLuint colorLoc = glGetUniformLocation(shader->ID, "objectColor");
    glUniform4fv(colorLoc, 1, glm::value_ptr(color));
}