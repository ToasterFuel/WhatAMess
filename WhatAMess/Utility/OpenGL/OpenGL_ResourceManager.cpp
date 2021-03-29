#include "OpenGL_ResourceManager.h"

#include <stdlib.h>
#include <stb_image.h>

Image OpenGL_ResourceManager::GetImage(const char* path, int* error)
{
    if(!FileExists(path))
    {
        *error = RESOURCE_DOES_NOT_EXIST;
        return Image(nullptr, 0, 0, 0, nullptr);
    }
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    return Image(data, width, height, nrChannels, data);
}

std::string OpenGL_ResourceManager::GetFile(const char* path, int* error)
{
    if(!FileExists(path))
    {
        *error = RESOURCE_DOES_NOT_EXIST;
        return std::string();
    }
    return std::string();
}

void OpenGL_ResourceManager::FreeImage(Image image)
{
    stbi_image_free(image.data);
}

bool OpenGL_ResourceManager::FileExists(const char* path)
{
    if(path == nullptr)
        return false;
    FILE* file;

    if(fopen_s(&file, path, "r") == 0)
    {
        fclose(file);
        return true;
    }

    return false;
}
