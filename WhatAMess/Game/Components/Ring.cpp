#include "Ring.h"
#include "../../Graphics/Renderer.h"

void Ring::Init(glm::vec2 position, Shader* spriteShader, Texture2d* ringTexture)
{
    sprite = Sprite();
    sprite.Init(spriteShader, ringTexture, Color(), position);
}

void Ring::Render()
{
    Renderer::Instance().DrawSprite(sprite);
}
