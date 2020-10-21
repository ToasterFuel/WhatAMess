#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "Image.h"
#include <string>

#ifdef OPEN_GL_BUILD
#include "OpenGL/OpenGL_ResourceManager.h"
#endif

class ResourceManager
{
public:
    ResourceManager();
    Image GetImage(const char* path);
    std::string GetFile(const char* path);
    void FreeImage(Image image);

    static ResourceManager& Instance()
    {
        static ResourceManager instance;
        return instance;
    }
private:
#ifdef OPEN_GL_BUILD
    OpenGL_ResourceManager actualResourceManager;
#endif
};

#endif
