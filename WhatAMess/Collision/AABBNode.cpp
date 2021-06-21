#include "AABBNode.h"

void AABBNode::Init(BoundingBox boundingBox, AABBNode* parent, AABBNode* left, AABBNode* right, float fattenAmount)
{
    this->height = 0;
    this->originalBoundingBox = boundingBox;
    this->fattenedBoundingBox = boundingBox;
    fattenedBoundingBox.Extend(fattenAmount, fattenAmount);
    this->parent = parent;
    this->left = left;
    this->right = right;
}

void AABBNode::RecalculateBoundedBoxes(BoundingBox a, BoundingBox b, float fattenAmount)
{
    originalBoundingBox.Init(a, b);
    fattenedBoundingBox = originalBoundingBox;
    fattenedBoundingBox.Extend(fattenAmount, fattenAmount);
}
