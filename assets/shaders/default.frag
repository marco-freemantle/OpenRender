// GLSL Fragment Shader: Determines the color of the pixels (fragments).
#version 330 core
out vec4 FragColor;

in vec2 texCoord; // Receive the texture coordinates from the vertex shader

uniform sampler2D tex0;
uniform bool useTexture;
uniform vec4 objectColor;

void main()
{
   if (useTexture)
      FragColor = texture(tex0, texCoord);
   else
      FragColor = objectColor;
}