#include "Ring.h"
#include "../../Timing/Time.h"
#include "../../Graphics/Renderer.h"
#include "../../ObjectManagement/NodeHolder.h"
#include "../../Utility/RandomUtils.h"

void Ring::Init(glm::vec2 position, Shader* spriteShader, Texture2d* ringTexture)
{
    moveDirection = glm::vec2(RandomUtils::GetFroatFromRange(-1.0f, 1.0f), RandomUtils::GetFroatFromRange(-1.0f, 1.0f));
    moveDirection = glm::normalize(moveDirection);
    moveSpeed = RandomUtils::GetFroatFromRange(10, 40);
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
    glm::vec2 moveAmount = moveSpeed * Time::Instance().DeltaTime() * moveDirection;
    sprite.position += moveAmount;
    BoundingBox* boundingBox = NodeHolder::Instance().GetBoundingBox(boundingBoxId);
    boundingBox->Move(moveAmount);
}

void Ring::Render()
{
    Renderer::Instance().DrawSprite(sprite);
}
