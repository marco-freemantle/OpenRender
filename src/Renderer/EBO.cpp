#include "Renderer/EBO.h"

EBO::EBO(GLuint *indices, GLsizeiptr size)
{
    glGenBuffers(1, &ID); // Generate a buffer ID
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // Bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); // Upload index data to the buffer   
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // Bind the EBO for use
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the EBO (bind to 0)
}

void EBO::Delete()
{
    glDeleteBuffers(1, &ID); // Delete the buffer to free resources
}