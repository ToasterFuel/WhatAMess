#ifndef __AABB_NODE_H__
#define __AABB_NODE_H__

#include "BoundingBox.h"

class AABBNode
{
public:
    AABBNode* parent;
    AABBNode* left;
    AABBNode* right;
    BoundingBox boundingBox;
    int height;

    void Init(BoundingBox boundingBox, AABBNode* parent, AABBNode* left, AABBNode* right);
};

#endif