#ifndef __VECTOR_UTILS_H__
#define __VECTOR_UTILS_H__

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
};

#endif
