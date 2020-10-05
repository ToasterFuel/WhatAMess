#ifndef __TEXTURE_2D_H__
#define __TEXTURE_2D_H__

class Texture2d
{
public:
    Texture2d();
    void Generate(unsigned int width, unsigned int height, int numberOfBitsPerPixel, unsigned char* data);
    void Bind() const;

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
