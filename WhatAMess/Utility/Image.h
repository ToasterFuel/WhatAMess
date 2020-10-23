#ifndef __IMAGE_H__
#define __IMAGE_H__

struct Image
{
public:
    Image(unsigned char* data, unsigned int width,
            unsigned int height, unsigned int bitsPerPixel,
            void* originalData);
    unsigned char* data;
    unsigned int width;
    unsigned int height;
    unsigned int bitsPerPixel;
    void *originalData;
};

#endif