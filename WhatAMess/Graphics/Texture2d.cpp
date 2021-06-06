#include <iostream>

#ifdef OPEN_GL_BUILD
#include <glad/glad.h>
#elif WEB_GL_BUILD
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#endif

#include "Texture2d.h"

Texture2d::Texture2d() : id(0), width(0), height(0),
        internalFormat(GL_RGBA), imageFormat(GL_RGBA), wrapS(GL_REPEAT),
        wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMag(GL_LINEAR)
{
}

unsigned int Texture2d::GetWidth()
{
    return width;
}
unsigned int Texture2d::GetHeight()
{
    return height;
}

void Texture2d::SetFilter(TextureFilterMode filterMode)
{
    switch(filterMode)
    {
    case TEXTURE_NEAREST:
        filterMin = GL_NEAREST;
        filterMag = GL_NEAREST;
        break;
    case TEXTURE_LINEAR:
        filterMin = GL_LINEAR;
        filterMag = GL_LINEAR;
        break;
    }
}

void Texture2d::SetClamp(TextureClampMode clampModeX, TextureClampMode clampModeY)
{
    wrapS = GetGraphicsClamp(clampModeX);
    wrapT = GetGraphicsClamp(clampModeY);
}

unsigned int Texture2d::GetGraphicsClamp(TextureClampMode clampMode)
{
    switch(clampMode)
    {
    case TEXTURE_CLAMP:
        return GL_CLAMP_TO_EDGE;
    case TEXTURE_MIRROR_REPEAT:
        return GL_MIRRORED_REPEAT;
    case TEXTURE_REPEAT:
        return GL_REPEAT;
    }
    return GL_REPEAT;
}

void Texture2d::Generate(Image image)
{
    Generate(image.width, image.height, image.bitsPerPixel, image.data);
}

void Texture2d::Generate(unsigned int width, unsigned int height, int numberOfBitsPerPixel, unsigned char* data)
{
    if(numberOfBitsPerPixel == 3)
    {
        internalFormat = GL_RGB;
        imageFormat = GL_RGB;
    }
    else if(numberOfBitsPerPixel == 4)
    {
        internalFormat = GL_RGBA;
        imageFormat = GL_RGBA;
    }

    this->width = width;
    this->height = height;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    std::cout << "FilterMin: " << filterMin << " Nearest: " << GL_NEAREST << " Linear: " << GL_LINEAR << "\n";
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2d::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}
