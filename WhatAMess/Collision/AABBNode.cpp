#include "AABBNode.h"
#include "AABBSystem.h"
#include "../ObjectManagement/NodeHolder.h"
#include "BoundingBoxHelper.h"

void AABBNode::OriginalBoundingBoxMoved()
{
    if(!BoundingBoxHelper::FullyContains(fattenedBoundingBoxId, originalBoundingBoxId))
    {
        AABBSystem::Instance().RemoveBoundingBox(this);
        AABBSystem::Instance().AddBoundingBox(originalBoundingBoxId, this);
    }
}

void AABBNode::Init(int boundingBoxId, AABBNode* parent, AABBNode* left, AABBNode* right, float fattenAmount)
{
    NodeHolder& holder = NodeHolder::Instance();
    this->height = 0;
    this->originalBoundingBoxId = boundingBoxId;
    holder.CreateBoundingBox(&this->fattenedBoundingBoxId);
    BoundingBox* originalBoundingBox = holder.GetBoundingBox(boundingBoxId);
    originalBoundingBox->SetContainingNode(this);

    BoundingBox* fatBoundingBox = holder.GetBoundingBox(fattenedBoundingBoxId);
    fatBoundingBox->Init(originalBoundingBox);
    fatBoundingBox->Extend(fattenAmount, fattenAmount);
    this->parent = parent;
    this->left = left;
    this->right = right;
}

void AABBNode::RecalculateBoundedBoxes(int boundingBoxA, int boundingBoxB, float fattenAmount)
{
    BoundingBoxHelper::Init(originalBoundingBoxId, boundingBoxA, boundingBoxB);
    BoundingBoxHelper::ExtendFromOther(fattenedBoundingBoxId, originalBoundingBoxId, fattenAmount, fattenAmount);
}
