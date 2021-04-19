#ifndef __VECTOR_UTILS_H__
#define __VECTOR_UTILS_H__

#include "MathUtils.h"

#include <glm/glm.hpp>

class VectorUtils
{
public:
    static glm::vec3 UPv3;
    static glm::vec3 RIGHTv3;
    static glm::vec3 FORWARDv3;

    static glm::vec3 ToVec3(glm::vec2 data)
    {
        return glm::vec3(data, 0.0f);
    }

    static glm::vec2 Min(glm::vec2 a, glm::vec2 b)
    {
        return glm::vec2(MathUtils::Min(a.x, b.x), MathUtils::Min(a.y, b.y));
    }

    static glm::vec2 Max(glm::vec2 a, glm::vec2 b)
    {
        return glm::vec2(MathUtils::Max(a.x, b.x), MathUtils::Max(a.y, b.y));
    }

    static glm::vec2 FindCenter(glm::vec2 a, glm::vec2 b)
    {
        return glm::vec2((a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f);
    }
};

#endif
