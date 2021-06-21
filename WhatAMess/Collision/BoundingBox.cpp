#include "BoundingBox.h"
#include "../Utility/VectorUtils.h"

void BoundingBox::Init(glm::vec2 center, float radius)
{
    this->center = center;
    float halfRadius = radius / 2;
    min = glm::vec2(center.x - halfRadius, center.y - halfRadius);
    max = glm::vec2(center.x + halfRadius, center.y + halfRadius);
}

void BoundingBox::Init(BoundingBox a, BoundingBox b)
{
    min = VectorUtils::Min(a.min, b.min);
    max = VectorUtils::Max(a.max, b.max);
    center = VectorUtils::FindCenter(min, max);
}

void BoundingBox::Extend(float xAmount, float yAmount)
{
    glm::vec2 halfs(xAmount * 0.5f, yAmount * 0.5f);
    max += halfs;
    min -= halfs;
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

bool BoundingBox::FullyEncapsulates(BoundingBox& other)
{
    return other.GetMin().x > GetMin().x
        && other.GetMax().x < GetMax().x
        && other.GetMin().y > GetMin().y
        && other.GetMax().y < GetMax().y;
}

bool BoundingBox::FullyContainedIn(BoundingBox& other)
{
    return GetMin().x > other.GetMin().x
        && GetMax().x < other.GetMax().x
        && GetMin().y > other.GetMin().y
        && GetMax().y < other.GetMax().y;
}

bool BoundingBox::Overlaps(BoundingBox& other)
{
    //return maxx1 > minx2 && minx1 < maxx2 && maxy1 > miny2 && miny1 < maxy2
    return GetMax().x > other.GetMin().x
            && GetMin().x < other.GetMax().x
            && GetMax().y > other.GetMin().y
            && GetMin().y < other.GetMax().y;
}
