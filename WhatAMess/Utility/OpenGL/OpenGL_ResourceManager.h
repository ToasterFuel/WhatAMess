#ifndef __OPEN_GL_RESOURCE_MANAGER_H__
#define __OPEN_GL_RESOURCE_MANAGER_H__

#include "../Image.h"
#include <string>

class OpenGL_ResourceManager
{
public:
    Image GetImage(const char* path);
    std::string GetFile(const char* path);
    void FreeImage(Image image);
};

#endif
