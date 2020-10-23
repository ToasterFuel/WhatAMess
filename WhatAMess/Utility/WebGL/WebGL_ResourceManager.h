#ifndef __WEB_GL_RESOURCE_MANAGER_H__
#define __WEB_GL_RESOURCE_MANAGER_H__
#ifdef WEB_GL_BUILD

#include "../Image.h"
#include <string>

class WebGL_ResourceManager
{
public:
    Image GetImage(const char* path);
    std::string GetFile(const char* path);
    void FreeImage(Image image);
private:
    int InvertImage(int width, int height, void *image_pixels);
};

#endif
#endif