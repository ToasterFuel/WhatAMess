#include "ResourceManager.h"

ResourceManager::ResourceManager(): actualResourceManager()
{
}

Image ResourceManager::GetImage(const char* path)
{
    return actualResourceManager.GetImage(path);
}

std::string ResourceManager::GetFile(const char* path)
{
    return actualResourceManager.GetFile(path);
}

void ResourceManager::FreeImage(Image image)
{
    actualResourceManager.FreeImage(image);
}
