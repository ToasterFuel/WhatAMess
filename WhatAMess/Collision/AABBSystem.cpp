#include "AABBSystem.h"
#include "../Graphics/Renderer.h"
#include "../Utility/MathUtils.h"

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

AABBNode* AABBSystem::CreateNode(BoundingBox boundingBox, AABBNode* parent, AABBNode* left, AABBNode* right)
{
    AABBNode* node = new AABBNode();
    node->Init(boundingBox, parent, left, right, FATTEN_AMOUNT);
    if(left != nullptr)
        left->parent = node;
    if(right != nullptr)
        right->parent = node;
    return node;
}

void AABBSystem::AddBoundingBox(BoundingBox boundingBox)
{
    AABBNode* newNode = CreateNode(boundingBox, nullptr, nullptr, nullptr);
    if(root == nullptr)
    {
        root = newNode;
        return;
    }

    AABBNode* lastFitNode = nullptr;
    AABBNode* current = root;
    while(current->fattenedBoundingBox.Overlaps(newNode->fattenedBoundingBox))
    {
        bool leftChildOverlap = current->left != nullptr && current->left->fattenedBoundingBox.Overlaps(newNode->fattenedBoundingBox);
        bool rightChildOverlap = current->right != nullptr && current->right->fattenedBoundingBox.Overlaps(newNode->fattenedBoundingBox);
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
        BoundingBox containingBox = BoundingBox();
        containingBox.Init(newNode->fattenedBoundingBox, root->fattenedBoundingBox);
        root = CreateNode(containingBox, lastFitNode, newNode, root);
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
            BoundingBox containingBox = BoundingBox();
            containingBox.Init(newNode->fattenedBoundingBox, lastFitNode->fattenedBoundingBox);

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
            BoundingBox containingBox = BoundingBox();
            containingBox.Init(newNode->fattenedBoundingBox, oldChild->fattenedBoundingBox);

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
            current->RecalculateBoundedBoxes(current->left->fattenedBoundingBox, current->right->fattenedBoundingBox, FATTEN_AMOUNT);
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

    boundingSprite.sprite->position = node->fattenedBoundingBox.GetCenter();
    boundingSprite.sprite->scale.x = node->fattenedBoundingBox.GetWidth();
    boundingSprite.sprite->scale.y = node->fattenedBoundingBox.GetHeight();
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
