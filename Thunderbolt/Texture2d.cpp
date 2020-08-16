#include "Texture2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2d::Texture2d()
	:width(0),
	height(0),
	internalFormat(GL_RGB),
	imageFormat(GL_RGB),
	wrapS(GL_REPEAT),
	wrapT(GL_REPEAT),
	filterMin(GL_NEAREST),
	filterMax(GL_NEAREST)
{
	glGenTextures(1, &this->ID);
}

void Texture2d::load(const char* file, bool alpha)
{
    // create texture object
    if (alpha)
    {
        this->internalFormat = GL_RGBA;
        this->imageFormat = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    this->generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
}

void Texture2d::generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;
    
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2d::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
