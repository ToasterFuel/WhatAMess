#ifndef __RENDERER_H__
#define __RENDERER_H__

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

    void SyncCameraViewProjection(const Camera &camera);
    void DrawSprite(const Sprite &sprite) const;

private:
    glm::mat4 cameraView;
    glm::mat4 cameraProjection;
};
#endif