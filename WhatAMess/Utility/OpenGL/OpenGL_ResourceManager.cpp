#include "OpenGL_ResourceManager.h"

#include <stb_image.h>

Image OpenGL_ResourceManager::GetImage(const char* path)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    return Image(data, width, height, nrChannels, data);
}

std::string OpenGL_ResourceManager::GetFile(const char* path)
{
    return std::string();
}

void OpenGL_ResourceManager::FreeImage(Image image)
{
    stbi_image_free(image.data);
}
