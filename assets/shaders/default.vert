// GLSL Vertex Shader: Processes each vertex's position. 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTexCoord;

out vec3 colour;
out vec2 texCoord;

uniform float scale;

uniform mat4 camMatrix; // Combined View-Projection matrix


void main()
{
    gl_Position = camMatrix * vec4(aPos * scale, 1.0); // Apply transformations to the vertex position
    colour = aColour; // Pass the color to the fragment shader
    texCoord = aTexCoord; // Pass the texture coordinate to the fragment shader
}