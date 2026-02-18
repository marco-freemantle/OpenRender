// GLSL Fragment Shader: Determines the color of the pixels (fragments).
#version 330 core
out vec4 FragColor;

in vec3 colour; // Receive the color from the vertex shader
in vec2 texCoord; // Receive the texture coordinates from the vertex shader

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoord);
}