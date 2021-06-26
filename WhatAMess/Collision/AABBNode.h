#ifndef __AABB_NODE_H__
#define __AABB_NODE_H__

class AABBNode
{
public:
    AABBNode* parent;
    AABBNode* left;
    AABBNode* right;
    int originalBoundingBoxId;
    int fattenedBoundingBoxId;
    int height;

    void OriginalBoundingBoxMoved();
    void Init(int boundingBoxId, AABBNode* parent, AABBNode* left, AABBNode* right, float fattenAmount);
    void RecalculateBoundedBoxes(int boundingBoxA, int boundingBoxB, float fattenAmount);
};

#endif