#include "Render/Texture.h"

using namespace Hudson::Render;

Texture::Texture() {
    width = 0;
    height = 0;
    internalFormat = GL_RGB;
    imageFormat = GL_RGB;
    wrapS = GL_REPEAT;
    wrapT = GL_REPEAT;
    filterMin = GL_NEAREST;
    filterMax = GL_NEAREST;

    glGenTextures(1, &this->ID);
};

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;
    // create Texture

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}