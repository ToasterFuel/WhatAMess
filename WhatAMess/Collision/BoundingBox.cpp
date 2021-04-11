#include "BoundingBox.h"
#include "../Utility/VectorUtils.h"

void BoundingBox::Init(glm::vec2 center, float radius)
{
    this->center = center;
    min = glm::vec2(center.x - radius, center.y - radius);
    max = glm::vec2(center.x + radius, center.y + radius);
}

float BoundingBox::GetWidth()
{
    return max.x - min.x;
}

float BoundingBox::GetHeight()
{
    return max.y - min.y;
}

glm::vec2 BoundingBox::GetMin()
{
    return min;
}
glm::vec2 BoundingBox::GetMax()
{
    return max;
}

glm::vec2 BoundingBox::GetCenter()
{
    return center;
}
