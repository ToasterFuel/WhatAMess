#include "NodeHolder.h"

BoundingBox* NodeHolder::CreateBoundingBox(int* id)
{
    BoundingBox* newBoundingBox = new BoundingBox();
    boundingBoxHolder.push_back(newBoundingBox);
    *id = boundingBoxHolder.size() - 1;

    return newBoundingBox;
}

BoundingBox* NodeHolder::GetBoundingBox(int id)
{
    if(id < 0 || id >= boundingBoxHolder.size())
        return nullptr;
    return boundingBoxHolder[id];
}
