// GLSL Vertex Shader: Processes each vertex's position. 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 camMatrix; // Combined View-Projection matrix
uniform bool useTexture; // Flag to indicate if texture should be used

void main()
{
    gl_Position = camMatrix * vec4(aPos, 1.0); // Apply transformations to the vertex position
    texCoord = aTexCoord; // Pass the texture coordinate to the fragment shader
}