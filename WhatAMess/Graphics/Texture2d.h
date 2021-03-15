#ifndef __TEXTURE_2D_H__
#define __TEXTURE_2D_H__

#include "../Utility/Image.h"

class Texture2d
{
public:
    Texture2d();
    void Generate(Image image);
    void Generate(unsigned int width, unsigned int height, int numberOfBitsPerPixel, unsigned char* data);
    void Bind() const;

    unsigned int GetWidth();
    unsigned int GetHeight();

private:
    unsigned int id;
    unsigned int width;
    unsigned int height;
    unsigned int internalFormat;
    unsigned int imageFormat;
    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int filterMin;
    unsigned int filterMax;
};

#endif
