#ifndef __AABB_SYSTEM_H__
#define __AABB_SYSTEM_H__

#include "BoundingBox.h"
#include "AABBNode.h"
#include "../Graphics/NineSliceSprite.h"
#include "../Graphics/Sprite.h"

class AABBSystem
{
public:
    static AABBSystem& Instance()
    {
        static AABBSystem instance;
        return instance;
    }

    void Init(Shader* spriteShader, Texture2d* boxTexture, glm::vec4 nineSliceBorders);

    void AddBoundingBox(BoundingBox boundingBox);
    void RenderTree();
private:
    AABBNode* root;
    AABBNode* CreateNode(BoundingBox boundingBox, AABBNode* parent, AABBNode* left, AABBNode* right);
    /*
     * < 0 if left is lower
     * 0 if they are equal
     * > 0 if right is lower
     */
    int GetLowerNode(AABBNode* left, AABBNode*right);
    /*
     * < 0 if left is lower
     * 0 if they are equal
     * > 0 if right is lower
     */
    int GetLowerNode(AABBNode* parent);
    void RecalculateBounds(AABBNode* startNode);
    void RenderTree(AABBNode* node);

    Sprite boxSprite;
    NineSliceSprite boundingSprite;
    int renderRootHeight;
};

#endif