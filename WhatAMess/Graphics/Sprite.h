#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Texture2d.h"
#include "../Math/Vector3.h"
#include "Shader.h"
#include "../Utility/Color.h"

class Sprite
{
public:
    Sprite(Shader& shader, Texture2d& texture, Color color = Color(), Vector3 position = Vector3(), Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), float rotation = 0.0f);
    Sprite(Sprite&& other);
    Sprite();
    ~Sprite();
    void SetShaderData() const;

    Color color;
    Vector3 position;
    Vector3 scale;
    //Rotation is in degrees
    float rotation;

    Shader& shader;
    Texture2d& texture;
    unsigned int quadVAO;
};

#endif
