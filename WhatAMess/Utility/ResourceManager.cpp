#include "ResourceManager.h"

ResourceManager::ResourceManager(): actualResourceManager()
{
}

Image ResourceManager::GetImage(const char* path, int* error)
{
    return actualResourceManager.GetImage(path, error);
}

std::string ResourceManager::GetFile(const char* path, int* error)
{
    return actualResourceManager.GetFile(path, error);
}

void ResourceManager::FreeImage(Image image)
{
    actualResourceManager.FreeImage(image);
}
