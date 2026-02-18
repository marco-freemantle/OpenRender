// GLSL Vertex Shader: Processes each vertex's position. 
// "layout (location = 0)" matches the index we'll use in our VAO later.
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
}