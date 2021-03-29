#ifndef __OPEN_GL_RESOURCE_MANAGER_H__
#define __OPEN_GL_RESOURCE_MANAGER_H__

#include "../Image.h"
#include <string>

#define RESOURCE_DOES_NOT_EXIST 1

class OpenGL_ResourceManager
{
public:
    Image GetImage(const char* path, int* error);
    std::string GetFile(const char* path, int* error);
    void FreeImage(Image image);

private:
    bool FileExists(const char* path);
};

#endif
