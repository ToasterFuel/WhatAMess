#include "Ring.h"
#include "../../Timing/Time.h"
#include "../../Graphics/Renderer.h"
#include "../../ObjectManagement/NodeHolder.h"

void Ring::Init(glm::vec2 position, Shader* spriteShader, Texture2d* ringTexture)
{
    sprite = Sprite();
    sprite.Init(spriteShader, ringTexture, Color(), position);
    BoundingBox* boundingBox = NodeHolder::Instance().CreateBoundingBox(&boundingBoxId);
    boundingBox->Init(sprite.position, sprite.scale.x);
}

int Ring::GetBoundingBoxId()
{
    return boundingBoxId;
}

void Ring::Update()
{
    glm::vec2 moveAmount = 10 * Time::Instance().DeltaTime() * glm::vec2(1, 0);
    sprite.position += moveAmount;
    BoundingBox* boundingBox = NodeHolder::Instance().GetBoundingBox(boundingBoxId);
    boundingBox->Move(moveAmount);
}

void Ring::Render()
{
    Renderer::Instance().DrawSprite(sprite);
}
