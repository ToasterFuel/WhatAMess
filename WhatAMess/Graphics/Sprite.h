#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Texture2d.h"
#include "Shader.h"
#include "../Utility/Color.h"

class Sprite
{
public:
    Sprite();
    ~Sprite();
    void Init(Shader* shader, Texture2d* texture, Color color = Color(), glm::vec2 position = glm::vec2(0.0f, 0.0f), float rotation = 0.0f);
    void SetShaderData() const;

    Color color;
    glm::vec2 position;
    glm::vec2 scale;
    //Rotation is in degrees
    float rotation;

    Shader* shader;
    Texture2d* texture;
    unsigned int quadVAO;
};

#endif
