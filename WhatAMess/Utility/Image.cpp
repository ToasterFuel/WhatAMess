#include "Image.h"

Image::Image(unsigned char* data, unsigned int width,
        unsigned int height, unsigned int bitsPerPixel,
        void* originalData): data(data), width(width),
        height(height), bitsPerPixel(bitsPerPixel), originalData(originalData)
{
}