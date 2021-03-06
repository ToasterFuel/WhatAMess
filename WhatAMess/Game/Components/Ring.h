#ifndef __RING_H__
#define __RING_H__

#include "../../Graphics/Sprite.h"
#include "../../Graphics/Shader.h"
#include "../../Graphics/Texture2d.h"
#include "../../Collision/BoundingBox.h"

#include <glm/glm.hpp>

class Ring
{
public:
    void Init(glm::vec2 position, Shader* spriteShader, Texture2d* ringTexture);
    void Render();
    void Update();
    int GetBoundingBoxId();
private:
    glm::vec2 moveDirection;
    float moveSpeed;
    Sprite sprite;
    int boundingBoxId;
};

#endif
