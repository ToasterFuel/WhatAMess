#ifndef __AABB_SYSTEM_H__
#define __AABB_SYSTEM_H__

#include "BoundingBox.h"

class AABBSystem
{
public:
    static AABBSystem& Instance()
    {
        static AABBSystem instance;
        return instance;
    }

    //void AddBoundingBox(BoundingBox boundingBox);
};

#endif