#ifndef __BOUNDING_BOX_H__
#define __BOUNDING_BOX_H__

#include <glm/glm.hpp>

class BoundingBox
{
public:
    void Init(glm::vec2 center, float radius);
    void Init(BoundingBox a, BoundingBox b);

    float GetWidth();
    float GetHeight();
    glm::vec2 GetMin();
    glm::vec2 GetMax();
    glm::vec2 GetCenter();

    bool Overlaps(BoundingBox& other);

private:
    glm::vec2 min;
    glm::vec2 max;
    glm::vec2 center;
};

#endif
