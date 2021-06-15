#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "NineSliceSprite.h"
#include "Sprite.h"
#include "Camera.h"

class Renderer
{
public:
    static Renderer& Instance()
    {
        static Renderer instance;
        return instance;
    }

    void SyncCameraViewProjection(Camera &camera);
    void DrawNineSlice(const NineSliceSprite& sprite) const;
    void DrawSprite(const Sprite &sprite) const;

private:
    void RenderSprite(const Sprite &sprite) const;
    glm::mat4 cameraView;
    glm::mat4 cameraProjection;
};
#endif