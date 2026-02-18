#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>

#include "Shader.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLuint unit;
	Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

	static void BindTextureUnitToShader(Shader& shader, const char* uniform, GLuint uint);
	void Bind();
	void Unbind();
	void Delete();
};
#endif