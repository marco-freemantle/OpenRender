#include "Renderer/Texture.h"

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType)
{
    // Store the type of the texture (usually GL_TEXTURE_2D)
    type = texType;

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);

    // Load image data from file
    // The final parameter STBI_rgb_alpha forces the image to be loaded with 4 channels (RGBA)
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);

    // Generate one texture and store its ID
    glGenTextures(1, &ID);

    // ---------------------------------------------
    // EXPLANATION OF `slot` AND TEXTURE UNITS
    //
    // Modern GPUs can work with many textures at once.
    // Each texture must be assigned to a texture unit (GL_TEXTURE0, GL_TEXTURE1, etc.)
    //
    // `slot` is the texture unit index that you want this texture to be bound to.
    // For example, if `slot == 1`, the texture is bound to `GL_TEXTURE1`.
    // This allows you to use multiple textures in shaders.
    //
    // Later in your shader, you can reference this unit using a `sampler2D`
    // uniform like: uniform sampler2D myTexture;
    // and you set it to slot 1 with: glUniform1i(glGetUniformLocation(shaderID, "myTexture"), 1);
    // ---------------------------------------------

    // Activate the desired texture unit by adding the slot to GL_TEXTURE0
    glActiveTexture(GL_TEXTURE0 + slot);

	unit = slot;

    // Bind the texture so that all future texture commands will configure this one
    glBindTexture(texType, ID);

    // Set texture filtering parameters:
    // GL_NEAREST means no interpolation, so each pixel is rendered as-is (pixelated look)
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // for minifying
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // for magnifying

    // Set texture wrapping parameters:
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT); // Horizontal wrap (S-axis)
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT); // Vertical wrap (T-axis)

    // Upload the texture image to the GPU:
    // - level 0: base image level
    // - GL_RGBA: format for internal storage and source data
    // - widthImg, heightImg: dimensions of the image
    // - border must be 0
    // - GL_UNSIGNED_BYTE: each color component is an unsigned byte
    // - bytes: pointer to the image data (loaded previously, e.g., with stb_image)
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

    // Generate mipmaps for the texture, which helps with rendering at smaller scales
    glGenerateMipmap(texType);

    // Free the image data from CPU memory, since it's now on the GPU
    stbi_image_free(bytes);

    // Unbind the texture to prevent accidental modification
    glBindTexture(texType, 0);
}

void Texture::BindTextureUnitToShader(Shader& shader, const char* uniformName, GLuint textureUnit)
{
    GLuint textureUniform = glGetUniformLocation(shader.ID, uniformName);
    shader.Activate();
    glUniform1i(textureUniform, textureUnit); // This binds texture (with ID) to the texture target (type, e.g., GL_TEXTURE_2D) on the currently active texture unit.
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit); // Activate the texture unit (e.g. GL_TEXTURE0, GL_TEXTURE1, etc.)
    glBindTexture(type, ID); // Bind this texture object to the currently active texture unit
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}