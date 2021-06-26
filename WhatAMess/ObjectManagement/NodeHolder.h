#ifndef __NODE_HOLDER_H__
#define __NODE_HOLDER_H__

#include "../Collision/BoundingBox.h"

#include <vector>

class NodeHolder
{
public:
    static NodeHolder& Instance()
    {
        static NodeHolder instance;
        return instance;
    }

    BoundingBox* CreateBoundingBox(int* id);
    BoundingBox* GetBoundingBox(int id);
private:
    //TODO: Something about returning/reusing items here
    std::vector<BoundingBox*> boundingBoxHolder;
};

#endif