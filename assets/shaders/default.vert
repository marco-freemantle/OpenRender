// GLSL Vertex Shader: Processes each vertex's position. 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTexCoord;

out vec3 colour;
out vec2 texCoord;

uniform float scale;

void main()
{
    gl_Position = vec4(aPos * scale, 1.0); // Scale the vertex position and set it as the output position
    colour = aColour; // Pass the color to the fragment shader
    texCoord = aTexCoord; // Pass the texture coordinate to the fragment shader
}