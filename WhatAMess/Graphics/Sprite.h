#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2d.h"
#include "../Math/Vector3.h"
#include "Shader.h"

class Sprite
{
public:
    Sprite(Shader& shader, Texture2d& texture, Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), float rotation = 0.0f);
    ~Sprite();

    Vector3 position;
    Vector3 scale;
    //Rotation is in degrees
    float rotation;

    Shader& shader;
    Texture2d& texture;
    unsigned int quadVAO;
};

#endif
