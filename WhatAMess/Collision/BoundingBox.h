#ifndef __BOUNDING_BOX_H__
#define __BOUNDING_BOX_H__

#include "AABBNode.h"

#include <glm/glm.hpp>

class BoundingBox
{
public:
    BoundingBox();
    void Init(BoundingBox* other);
    void Init(glm::vec2 center, float radius);
    void Init(BoundingBox* a, BoundingBox* b);

    void SetContainingNode(AABBNode* containingNode);
    void Move(glm::vec2 moveAmount);
    void Extend(float xAmount, float yAmount);
    float GetWidth();
    float GetHeight();
    glm::vec2 GetMin();
    glm::vec2 GetMax();
    glm::vec2 GetCenter();

    bool FullyEncapsulates(BoundingBox* other);
    bool FullyContainedIn(BoundingBox* other);
    bool Overlaps(BoundingBox* other);

private:
    glm::vec2 min;
    glm::vec2 max;
    glm::vec2 center;

    AABBNode* containingNode;
};

#endif
