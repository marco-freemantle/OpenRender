#include "Renderer/VBO.h"

VBO::VBO(const GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID); // Generate a buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, ID); // Bind the buffer to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Upload vertex data to the buffer   
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID); // Bind the buffer to the GL_ARRAY_BUFFER target
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer from the GL_ARRAY_BUFFER target
}

void VBO::Delete()
{
    glDeleteBuffers(1, &ID); // Delete the buffer to free GPU memory
}
