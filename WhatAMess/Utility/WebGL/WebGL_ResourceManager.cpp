#ifdef WEB_GL_BUILD
#include "WebGL_ResourceManager.h"

//#include <SDL.h>
//#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

Image WebGL_ResourceManager::GetImage(const char* path)
{
    SDL_Surface *image = IMG_Load(path);
    InvertImage(image->w * image->format->BytesPerPixel, image->h, (char *)image->pixels);

    return Image((unsigned char*)image->pixels, image->w, image->h, image->format->BytesPerPixel, (void*)image);
}

std::string WebGL_ResourceManager::GetFile(const char* path)
{
    return std::string();
}

void WebGL_ResourceManager::FreeImage(Image image)
{
    SDL_FreeSurface((SDL_Surface *)image.originalData);
}

int WebGL_ResourceManager::InvertImage(int width, int height, void *image_pixels)
{
    auto temp_row = std::unique_ptr<char>(new char[width]);
    if(temp_row.get() == nullptr)
    {
        std::cout << "Not enough memory for image inversion\n";
        return -1;
    }
    //if height is odd, don't need to swap middle row
    int height_div_2 = height / 2;
    for(int index = 0; index < height_div_2; index++)
    {
        //uses string.h
        memcpy((uint8_t *)temp_row.get(),
            (uint8_t *)(image_pixels)+
            width * index,
            width);

        memcpy(
            (uint8_t *)(image_pixels)+
            width * index,
            (uint8_t *)(image_pixels)+
            width * (height - index - 1),
            width);
        memcpy(
            (uint8_t *)(image_pixels)+
            width * (height - index - 1),
            temp_row.get(),
            width);
    }
    return 0;
}
#endif
