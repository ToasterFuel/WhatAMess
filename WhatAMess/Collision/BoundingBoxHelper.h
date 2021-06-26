#ifndef __BOUNDING_BOX_HELPER_H__
#define __BOUNDING_BOX_HELPER_H__

#include "../ObjectManagement/NodeHolder.h"

class BoundingBoxHelper
{
public:
    static bool FullyContains(int larger, int smaller)
    {
        BoundingBox* boundingBoxSmaller = NodeHolder::Instance().GetBoundingBox(smaller);
        BoundingBox* boundingBoxLarger = NodeHolder::Instance().GetBoundingBox(larger);
        if(boundingBoxSmaller == nullptr || boundingBoxLarger == nullptr)
            return false;
        return boundingBoxLarger->FullyEncapsulates(boundingBoxSmaller);
    }

    static bool Overlaps(int idA, int idB)
    {
        BoundingBox* boundingBoxA = NodeHolder::Instance().GetBoundingBox(idA);
        BoundingBox* boundingBoxB = NodeHolder::Instance().GetBoundingBox(idB);
        if(boundingBoxA == nullptr || boundingBoxB == nullptr)
            return false;

        return boundingBoxA->Overlaps(boundingBoxB);
    }

    static int CreateAndInit(int idA, int idB)
    {
        int id = -1;
        NodeHolder::Instance().CreateBoundingBox(&id);
        Init(id, idA, idB);

        return id;
    }

    static void ExtendFromOther(int idBase, int idOther, float x, float y)
    {
        BoundingBox* base = NodeHolder::Instance().GetBoundingBox(idBase);
        BoundingBox* other = NodeHolder::Instance().GetBoundingBox(idOther);
        base->Init(other);
        base->Extend(x, y);
    }

    static void Init(int idBase, int idA, int idB)
    {
        BoundingBox* boundingBoxBase = NodeHolder::Instance().GetBoundingBox(idBase);
        BoundingBox* boundingBoxA = NodeHolder::Instance().GetBoundingBox(idA);
        BoundingBox* boundingBoxB = NodeHolder::Instance().GetBoundingBox(idB);

        boundingBoxBase->Init(boundingBoxA, boundingBoxB);
    }
};

#endif