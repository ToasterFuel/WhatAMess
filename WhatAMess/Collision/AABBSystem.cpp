#include "AABBSystem.h"
#include "../Graphics/Renderer.h"
#include "../Utility/MathUtils.h"
#include "BoundingBoxHelper.h"

#include <iostream>

#define FATTEN_AMOUNT 10

void AABBSystem::Init(Shader* spriteShader, Texture2d* boxTexture, glm::vec4 nineSliceBorders)
{
    boxSprite = Sprite();
    boxSprite.Init(spriteShader, boxTexture, Color(), glm::vec2());

    boundingSprite = NineSliceSprite();
    boundingSprite.Init(&boxSprite, nineSliceBorders);
}

int AABBSystem::GetLowerNode(AABBNode* parent)
{
    if(parent == nullptr)
        return 0;
    return GetLowerNode(parent->left, parent->right);
}

int AABBSystem::GetLowerNode(AABBNode* left, AABBNode* right)
{
    if(left == nullptr && right == nullptr)
        return 0;
    if(left == nullptr && right != nullptr)
        return 1;
    if(left != nullptr && right == nullptr)
        return -1;
    return left->height - right->height;
}

AABBNode* AABBSystem::CreateNode(int boundingBoxId, AABBNode* parent, AABBNode* left, AABBNode* right)
{
    AABBNode* node = new AABBNode();
    node->Init(boundingBoxId, parent, left, right, FATTEN_AMOUNT);
    if(left != nullptr)
        left->parent = node;
    if(right != nullptr)
        right->parent = node;
    return node;
}

void AABBSystem::RemoveBoundingBox(AABBNode* existingNode)
{
    if(existingNode->left != nullptr)
        std::cout << "OMG This has a left child!\n";
    if(existingNode->right != nullptr)
        std::cout << "OMG This has a right child!\n";
    if(existingNode->parent == nullptr)
    {
        std::cout << "In here!\n";
        root = nullptr;
        return;
    }

    //God this is messy, can I clean it up at all?
    AABBNode* originalParentNode = root->parent;
    root->parent = nullptr;
    bool isLeftChild = originalParentNode->left == existingNode;
    if(isLeftChild)
    {
        originalParentNode->right->parent = originalParentNode->parent;
    }
    else
    {
        originalParentNode->left->parent = originalParentNode->parent;
    }

    if(originalParentNode != nullptr)
    {
        if(originalParentNode->parent->right == originalParentNode)
        {
            if(isLeftChild)
            {
                originalParentNode->parent->right = originalParentNode->right;
            }
            else
            {
                originalParentNode->parent->right = originalParentNode->left;
            }
        }
        else
        {
            if(isLeftChild)
            {
                originalParentNode->parent->left = originalParentNode->right;
            }
            else
            {
                originalParentNode->parent->left = originalParentNode->left;
            }
        }
        originalParentNode->right = nullptr;
        originalParentNode->left = nullptr;
    }

    /*
     * The parentNode had allocated 2 bounding boxes that are not being cleaned up heres
     * (Along with all the other reasons that delete shouldn't be called here)
     */
    delete originalParentNode;
}

void AABBSystem::AddBoundingBox(int boundingBoxId, AABBNode* existingNode)
{
    AABBNode* newNode = existingNode;
    if(newNode == nullptr)
        newNode = CreateNode(boundingBoxId, nullptr, nullptr, nullptr);
    if(root == nullptr)
    {
        std::cout << "Inserting!\n";
        root = newNode;
        return;
    }

    AABBNode* lastFitNode = nullptr;
    AABBNode* current = root;
    while(BoundingBoxHelper::Overlaps(current->fattenedBoundingBoxId, newNode->fattenedBoundingBoxId))
    {
        bool leftChildOverlap = current->left != nullptr && BoundingBoxHelper::Overlaps(current->left->fattenedBoundingBoxId, newNode->fattenedBoundingBoxId);
        bool rightChildOverlap = current->right != nullptr && BoundingBoxHelper::Overlaps(current->right->fattenedBoundingBoxId, newNode->fattenedBoundingBoxId);
        if(!leftChildOverlap && !rightChildOverlap)
        {
            lastFitNode = current;
            break;
        }
        if (leftChildOverlap && rightChildOverlap)
        {
            if(GetLowerNode(current) > 0)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        else if (leftChildOverlap)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        lastFitNode = current;
    }

    if(lastFitNode == nullptr)
    {
        int containingBoxId = BoundingBoxHelper::CreateAndInit(newNode->fattenedBoundingBoxId, root->fattenedBoundingBoxId);
        root = CreateNode(containingBoxId, lastFitNode, newNode, root);
    }
    else
    {
        bool rightNodeLower = GetLowerNode(lastFitNode) > 0;
        AABBNode* oldChild = lastFitNode->left;
        if(rightNodeLower)
            oldChild = lastFitNode->right;

        //If the child is null, that means the new boundingbox is overlapping with the lastFitNode
        if(oldChild == nullptr)
        {
            int containingBox = BoundingBoxHelper::CreateAndInit(newNode->fattenedBoundingBoxId, lastFitNode->fattenedBoundingBoxId);
            AABBNode* createdNode = CreateNode(containingBox, lastFitNode->parent, newNode, lastFitNode);
            if(createdNode->parent == nullptr)
            {
                root = createdNode;
            }
            else if(createdNode->parent->left == lastFitNode)
            {
                createdNode->parent->left = createdNode;
            }
            else
            {
                createdNode->parent->right = createdNode;
            }
        }
        else
        {
            int containingBox = BoundingBoxHelper::CreateAndInit(newNode->fattenedBoundingBoxId, oldChild->fattenedBoundingBoxId);

            if(rightNodeLower)
            {
                AABBNode* parentNode = CreateNode(containingBox, lastFitNode, newNode, oldChild);
                lastFitNode->right = parentNode;
            }
            else
            {
                AABBNode* parentNode = CreateNode(containingBox, lastFitNode, oldChild, newNode);
                lastFitNode->left = parentNode;
            }
        }
    }

    RecalculateBounds(newNode);
}

void AABBSystem::RecalculateBounds(AABBNode* startNode)
{
    AABBNode* current = startNode;
    while(current != nullptr)
    {
        if(current->left != nullptr && current->right != nullptr)
        {
            current->RecalculateBoundedBoxes(current->left->fattenedBoundingBoxId, current->right->fattenedBoundingBoxId, FATTEN_AMOUNT);
            current->height = MathUtils::Max(current->left->height, current->right->height) + 1;
        }
        current = current->parent;
    }
}

void AABBSystem::RenderTree()
{
    if(root != nullptr)
        renderRootHeight = root->height + 1;
    else
        renderRootHeight = 0;
    RenderTree(root, RENDER_DIR_ROOT);
}

void AABBSystem::RenderTree(AABBNode* node, RenderDirection renderDir)
{
    if(node == nullptr)
        return;

    RenderTree(node->left, RENDER_DIR_LEFT);
    RenderTree(node->right, RENDER_DIR_RIGHT);

    BoundingBox* boundingBox = NodeHolder::Instance().GetBoundingBox(node->fattenedBoundingBoxId);
    boundingSprite.sprite->position = boundingBox->GetCenter();
    boundingSprite.sprite->scale.x = boundingBox->GetWidth();
    boundingSprite.sprite->scale.y = boundingBox->GetHeight();
    float percentHeight = (float)node->height / (float)renderRootHeight;
    switch (renderDir)
    {
    case RENDER_DIR_ROOT:
        boundingSprite.sprite->color = Color(1, 1, 1, 1);
        break;
    case RENDER_DIR_LEFT:
        boundingSprite.sprite->color = Color(percentHeight, 0, 0, 1);
        break;
    case RENDER_DIR_RIGHT:
        boundingSprite.sprite->color = Color(0, 0, percentHeight, 1);
        break;
    default:
        boundingSprite.sprite->color = Color(percentHeight, percentHeight, percentHeight, 1);
        break;
    }
    Renderer::Instance().DrawNineSlice(boundingSprite);
}
