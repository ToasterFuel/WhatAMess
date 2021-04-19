#include "AABBSystem.h"
#include "../Graphics/Renderer.h"
#include "../Utility/MathUtils.h"

void AABBSystem::Init(Shader* spriteShader, Texture2d* boxTexture)
{
    squareSprite = Sprite();
    squareSprite.Init(spriteShader, boxTexture, Color(), glm::vec2());
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
    node->Init(boundingBox, nullptr, nullptr, nullptr);
    return node;
}

void AABBSystem::AddBoundingBox(BoundingBox boundingBox)
{
    Test this and do 9 splicing??
    AABBNode* newNode = CreateNode(boundingBox, nullptr, nullptr, nullptr);
    if(root == nullptr)
    {
        root = newNode;
        return;
    }

    AABBNode* lastFitNode = nullptr;
    AABBNode* current = root;
    while(current->boundingBox.Overlaps(boundingBox))
    {
        bool leftChildOverlap = current->left != nullptr && current->left->boundingBox.Overlaps(boundingBox);
        bool rightChildOverlap = current->right != nullptr && current->right->boundingBox.Overlaps(boundingBox);
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
        containingBox.Init(boundingBox, root->boundingBox);
        root = CreateNode(containingBox, lastFitNode, newNode, root);
    }
    else
    {
        bool rightNodeLower = GetLowerNode(lastFitNode) > 0;
        AABBNode* oldChild = lastFitNode->left;
        if(rightNodeLower)
            AABBNode* oldRight = lastFitNode->right;

        BoundingBox containingBox = BoundingBox();
        containingBox.Init(boundingBox, oldChild->boundingBox);

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

    RecalculateBounds(newNode);
}

void AABBSystem::RecalculateBounds(AABBNode* startNode)
{
    AABBNode* current = startNode;
    while(current != nullptr)
    {
        if(current->left != nullptr && current->right != nullptr)
        {
            current->boundingBox.Init(current->left->boundingBox, current->right->boundingBox);
            current->height = MathUtils::Max(current->left->height, current->right->height) + 1;
        }
        current = current->parent;
    }
}

void AABBSystem::RenderTree()
{
    RenderTree(root);
}

void AABBSystem::RenderTree(AABBNode* node)
{
    if(node == nullptr)
        return;
    RenderTree(node->left);
    RenderTree(node->right);
    squareSprite.position = node->boundingBox.GetCenter();
    squareSprite.scale.x = node->boundingBox.GetWidth();
    squareSprite.scale.y = node->boundingBox.GetHeight();
    Renderer::Instance().DrawSprite(squareSprite);
}
