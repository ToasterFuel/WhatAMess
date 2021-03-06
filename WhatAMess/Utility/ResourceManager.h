#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "Image.h"
#include <string>

#ifdef OPEN_GL_BUILD
#include "OpenGL/OpenGL_ResourceManager.h"
#elif WEB_GL_BUILD
#include "WebGL/WebGL_ResourceManager.h"
#endif

class ResourceManager
{
public:
    ResourceManager();
    Image GetImage(const char* path, int* error);
    std::string GetFile(const char* path, int* error);
    void FreeImage(Image image);

    static ResourceManager& Instance()
    {
        static ResourceManager instance;
        return instance;
    }
private:
#ifdef OPEN_GL_BUILD
    OpenGL_ResourceManager actualResourceManager;
#elif WEB_GL_BUILD
    WebGL_ResourceManager actualResourceManager;
#endif
};

#endif
