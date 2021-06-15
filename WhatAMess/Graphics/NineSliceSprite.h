#ifndef __NINE_SLICE_SPRITE_H__
#define __NINE_SLICE_SPRITE_H__

#include "Sprite.h"
#include <glm/glm.hpp>

class NineSliceSprite
{
public:
    NineSliceSprite();
    void Init(Sprite* sprite, glm::vec4 borders);
    void SetShaderData() const;

    Sprite* sprite;
    //Should be in the format <% from left, % from bottom, % from right, % from top>
    glm::vec4 borders;
private:
    glm::vec2 originalScale;
};

#endif
