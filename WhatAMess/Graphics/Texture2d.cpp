#include <iostream>
#include <glad/glad.h>

#include "Texture2d.h"

Texture2d::Texture2d() : width(0), height(0),
        internalFormat(GL_RGBA), imageFormat(GL_RGBA), wrapS(GL_REPEAT),
        wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
}

void Texture2d::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2d::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}