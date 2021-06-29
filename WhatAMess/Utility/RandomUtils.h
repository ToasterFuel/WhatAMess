#ifndef __RANDOM_UTILS_H__
#define __RANDOM_UTILS_H__
#include <cstdlib>

class RandomUtils
{
public:
    static float GetFroatFromRange(float low, float high)
    {
        return low + ((float)rand()) / (((float)RAND_MAX / (high - low)));
    }
};

#endif