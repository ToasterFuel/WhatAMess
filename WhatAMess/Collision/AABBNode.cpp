#include "AABBNode.h"

void AABBNode::Init(BoundingBox boundingBox, AABBNode* parent, AABBNode* left, AABBNode* right)
{
    this->height = 0;
    this->boundingBox = boundingBox;
    this->parent = parent;
    this->left = left;
    this->right = right;
}
