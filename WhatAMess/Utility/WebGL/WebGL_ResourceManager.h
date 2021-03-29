#ifndef __WEB_GL_RESOURCE_MANAGER_H__
#define __WEB_GL_RESOURCE_MANAGER_H__
#ifdef WEB_GL_BUILD

#include "../Image.h"
#include <string>

#define RESOURCE_DOES_NOT_EXIST 1

class WebGL_ResourceManager
{
public:
    Image GetImage(const char* path, int* error);
    std::string GetFile(const char* path, int* error);
    void FreeImage(Image image);
private:
    int InvertImage(int width, int height, void *image_pixels);
    bool FileExists(const char* path);
};

#endif
#endif