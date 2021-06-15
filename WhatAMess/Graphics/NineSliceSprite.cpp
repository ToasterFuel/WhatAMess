#include "NineSliceSprite.h"

NineSliceSprite::NineSliceSprite() : originalScale(glm::vec2(0, 0))
{
    sprite = nullptr;
}

void NineSliceSprite::Init(Sprite* sprite, glm::vec4 borders)
{
    this->sprite = sprite;
    this->borders = borders;
    originalScale = sprite->scale;
}

void NineSliceSprite::SetShaderData() const
{
    sprite->SetShaderData();
    sprite->shader->SetVector4f("borders", borders);
    sprite->shader->SetVector4f("scales", glm::vec4(originalScale, sprite->scale));
}